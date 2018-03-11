//
//  lexer.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/lexer.hpp"
#include "../include/lets.hpp"

#include "../include/operator.hpp"
#include "../include/keyword.hpp"

#include "../include/exception/error.h"
#include "../include/exception/lexer.h"

#define Lets_LEXER_SAVE_POS() \
	int back_row = this->row; \
	int back_col = this->col;
#define Lets_LEXER_GET_POS() \
	back_row, back_col

#define Lets_PUSH_BUFFER(T) \
	this->buffer.push_back(T);

#define Lets_PUSH_TOKEN(TYPE, THE_KW, THE_OP, TXT, R, C) \
	this->tokens.push_back(Token(TYPE, THE_KW, THE_OP, TXT, R, C));

lets_str_t Lexer::OPERATORS_CHARS = "+-*\\/%()[]{}=<>!&|,^~?:.@";

lets_vector_t<Token> Lexer::tokenize(){

	while (this->pos < this->length) {
		char current = peek(0);
		if(isdigit(current)) tokenize_number();
		else if(is_word_var(current)) tokenize_word();
		else if( current == '`') tokenize_extended_word();
		else if( current == '"' && look_char(1, '"') && look_char(2, '"')) tokenize_multiln_comment_dq();
		else if( current == '\'' && look_char(1, '\'') && look_char(2, '\'')) tokenize_multiln_comment_sq();
		else if( current == '"') tokenize_text_double_quote();
		else if( current == '\'') tokenize_text_single_quote();
		else if( current == '#') tokenize_comment();
		else if (find_c(OPERATORS_CHARS, current) != -1) tokenize_operator();
		else next();
	}

	return this->tokens;
}

void Lexer::tokenize_number() {

	clear_buffer();
	char current = peek(0);

	bool is_octal = (current == '0' && find_c("0123456789", peek(1)) != -1);

	if(current == '0' && look_char(1, 'x')){
		tokenize_hex_number();
		return;
	}

	if(current == '0' && look_char(1, 'b')){
		tokenize_binary_number();
		return;
	}

	while (true) {

		if(current == '.') {
			if(find_c(this->buffer, '.') != -1 || is_octal)
				throw LexerException(ExceptionsError::L_INVALID_FLOAT, this->row, this->col);
			else if(!isdigit(peek(1)))
				break;
		} else if(current == '_') {
			current = next();
			continue;
		} else if(!isdigit(current)){
			break;
		}

		Lets_PUSH_BUFFER(current)
		current = next();
	}

	if(is_octal){
		add_token(TT_OCTAL_NUMBER, this->buffer);
	} else {
		add_token(TT_NUMBER, this->buffer);
	}
}

void Lexer::tokenize_hex_number() {

	clear_buffer();
	next();
	next();

	char current = peek(0);

	while (is_hex_number(current) != -1) {
		Lets_PUSH_BUFFER(current)
		current = next();
	}

	add_token(TT_HEX_NUMBER, this->buffer);
}

int Lexer::is_hex_number(char c){
	return find_c("0123456789abcdef", tolower(c, std::locale()));
}

void Lexer::tokenize_binary_number() {

	next();
	next();
	clear_buffer();

	char current = peek(0);
	lets_str_t cur_s;
	while (true) {
		cur_s = current;
		// cur_s.push_back(current);
		if(std::regex_match(cur_s, std::regex("^[01]+$")) == 0)
			break;

		Lets_PUSH_BUFFER(current)
		current = next();
	}

	add_token(TT_BINARY_NUMBER, this->buffer);
}

void Lexer::tokenize_word() {

	clear_buffer();
	char current = peek(0);

	int start_row = this->row;
	int start_col = this->col - 1;


	while (true) {
		if(!(isdigit(current) || is_word_var(current))){
			break;
		}

		Lets_PUSH_BUFFER(current)
		current = next();
	}

	if(GET_KW_BY(this->buffer) != GET_KW(NIL)){
		add_token_kw(GET_KW_BY(this->buffer), this->buffer, start_row, start_col);
	} else {
		add_token(TT_IDENTIFIER, this->buffer, start_row, start_col);
	}
}

void Lexer::tokenize_extended_word() {

	Lets_LEXER_SAVE_POS()

	next(); // skip `
	clear_buffer();

	char current = peek(0);


	while (true) {
		if (current == '`') break;
		if (current == '\0') throw LexerException(ExceptionsError::L_EOF_EXTEND_WORD, Lets_LEXER_GET_POS());
		if (current == '\n' || current == '\r') throw LexerException(ExceptionsError::L_EOL_EXTEND_WORD, Lets_LEXER_GET_POS());
		Lets_PUSH_BUFFER(current)
		current = next();
	}
	next(); // skip closing `
	add_token(TT_IDENTIFIER, this->buffer);
}

void Lexer::tokenize_text_double_quote() {

	Lets_LEXER_SAVE_POS()

	next();
	clear_buffer();

	char current = peek(0);


	while (true) {

		if(current == '\\'){
			current = next();
			switch (current) {
				case '\\': current = next(); this->buffer.push_back('\\'); continue;
				case '"': current = next(); this->buffer.push_back('\"'); continue;
				case 'n': current = next(); this->buffer.push_back('\n'); continue;
				case 't': current = next(); this->buffer.push_back('\t'); continue;
				case 'b': current = next(); this->buffer.push_back('\b'); continue;
				case 'r': current = next(); this->buffer.push_back('\r'); continue;
				case '0': current = next(); this->buffer.push_back('\0'); continue;
			}
			this->buffer.push_back('\\');
			continue;
		}

		if(current == '"') break;
		if (current == '\0') throw LexerException(ExceptionsError::L_REACHED_EOF, Lets_LEXER_GET_POS());
		Lets_PUSH_BUFFER(current)
		current = next();
	}

	next();

	add_token(TT_STRING , this->buffer);
}

void Lexer::tokenize_text_single_quote() {

	Lets_LEXER_SAVE_POS()

	next();
	clear_buffer();

	char current = peek(0);


	while (true) {
		if(current == '\\'){
			current = next();
			switch (current) {
				case '\\': current = next(); this->buffer.push_back('\\'); continue;
				case '\'': current = next(); this->buffer.push_back('\''); continue;
			}
			this->buffer.push_back('\\');
			continue;
		}

		if(current == '\'') break;
		if (current == '\0') throw LexerException(ExceptionsError::L_REACHED_EOF, Lets_LEXER_GET_POS());
		Lets_PUSH_BUFFER(current)
		current = next();
	}

	next();

	add_token(TT_STRING, this->buffer);
}

void Lexer::tokenize_operator() {

	char current = peek(0);
	lets_str_t text;
	clear_buffer();

	while (true) {
		text = this->buffer;
		if(!text.empty() && GET_OP_BY(text + current) == GET_OP(NIL)){
			add_token_op(GET_OP_BY(text), text);
			return;
		}

		Lets_PUSH_BUFFER(current)
		current = next();
	}
}

void Lexer::tokenize_comment(){
	next();
	char current = peek(0);
	if(current == '*' and peek(1) == '-' and peek(2) == '*'){
		next(); next();
		lets_str_t buf;
		while (true) {
			current = next();
			if(current == '\r' or current == '\n' or current == '\0') return;
			if(current == '*' and peek(1) == '-' and peek(2) == '*') break;
			if(current == ' ') continue;
			buf.push_back(current);
		}
		if(buf == "FunctionAdder") Lets::ModeFunctionAdder = true;
	}
	while (current != '\r' && current != '\n' && current != '\0') {
		current = next();
	}
}

void Lexer::tokenize_multiln_comment_dq(){

	Lets_LEXER_SAVE_POS()

	next(); next(); next();

	char current = peek(0);
	while (true) {
		if(current == '"' && look_char(1, '"') && look_char(2, '"')) break;
		if(current == '\0') throw LexerException(ExceptionsError::L_MISS_CLOSE_TAG, Lets_LEXER_GET_POS());
		current = next();
	}

	next(); next(); next();
}

void Lexer::tokenize_multiln_comment_sq(){

	Lets_LEXER_SAVE_POS()

	next(); next(); next();

	char current = peek(0);
	while (true) {
		if(current == '\'' && look_char(1, '\'') && look_char(2, '\'')) break;
		if(current == '\0') throw LexerException(ExceptionsError::L_MISS_CLOSE_TAG, Lets_LEXER_GET_POS());
		current = next();
	}

	next(); next(); next();
}

bool Lexer::look_char(u_tt_t rpos, char chr){
	return peek(rpos) == chr;
}

char Lexer::next(){
	this->pos++;
	char res = peek(0);

	if(res == '\n'){
		this->row++;
		this->col = 1;
	} else {
		this->col++;
	}

	return res;
}

char Lexer::peek(u_tt_t rpos){
	int position = this->pos + rpos;
	if(position >= this->length) return '\0';
	return this->input[position];
}

void Lexer::clear_buffer(){
	buffer = "";
}

bool Lexer::is_word_var(char c){
	return isalpha(c, std::locale()) || (c == '_') || (c == '$') || (c == '@');
}

int Lexer::find_c(const lets_str_t& s, char c) {
	std::size_t pos = s.find(c);
	return (pos == lets_str_t::npos) ? -1 : (int)pos; 
}

void Lexer::add_token_kw(u_tt_t kw, const lets_str_t& txt, size_t r, size_t c){
	Lets_PUSH_TOKEN(TT_KEYWORD, kw, GET_OP(NIL), txt, r, c)
}

void Lexer::add_token_op(u_tt_t op, const lets_str_t& txt){
	Lets_PUSH_TOKEN(TT_OPERATOR, GET_KW(NIL), op, txt, this->row, this->col)
}

void Lexer::add_token(u_tt_t tt){
	this->add_token(tt, "");
}

void Lexer::add_token(u_tt_t tt, size_t r, size_t c){
	this->add_token(tt, "", r, c);
}

void Lexer::add_token(u_tt_t tt, const lets_str_t& txt){
	this->add_token(tt, txt, this->row, this->col);
}

void Lexer::add_token(u_tt_t tt, const lets_str_t& txt, size_t r, size_t c){
	Lets_PUSH_TOKEN(tt, GET_KW(NIL), GET_OP(NIL), txt, r, c)
}
