//
//  lexer.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/lexer.hpp"
#include "../include/lets.hpp"

#include "../include/exception/error.h"
#include "../include/exception/lexer.h"

#define Lets_LEXER_SAVE_POS() \
	int back_row = this->row; \
	int back_col = this->col;
#define Lets_LEXER_GET_POS() \
	back_row, back_col

#define Lets_PUSH_BUFFER(T) \
	this->buffer.push_back(T);

lets_str_t Lexer::OPERATORS_CHARS = "+-*\\/%()[]{}=<>!&|,^~?:.@";
lets_map_t<lets_str_t, u_tt_t> Lexer::OPERATORS = {
	{TT_PLUS_TEXT, TT_PLUS},
	{TT_MINUS_TEXT, TT_MINUS},
	{TT_STAR_TEXT, TT_STAR},
	{TT_BACKSLASH_TEXT, TT_BACKSLASH},
	{TT_SLASH_TEXT, TT_SLASH},
	{TT_PERCENT_TEXT, TT_PERCENT},
	{TT_LPAREN_TEXT, TT_LPAREN},
	{TT_RPAREN_TEXT, TT_RPAREN},
	{TT_LBRACKET_TEXT, TT_LBRACKET},
	{TT_RBRACKET_TEXT, TT_RBRACKET},
	{TT_LBRACE_TEXT, TT_LBRACE},
	{TT_RBRACE_TEXT, TT_RBRACE},
	{TT_EQ_TEXT, TT_EQ},
	{TT_LT_TEXT, TT_LT},
	{TT_GT_TEXT, TT_GT},
	{TT_COMMA_TEXT, TT_COMMA},
	{TT_DOT_TEXT, TT_DOT},
	{TT_CARET_TEXT, TT_CARET},
	{TT_TILDE_TEXT, TT_TILDE},
	{TT_QUESTION_TEXT, TT_QUESTION},
	{TT_COLON_TEXT, TT_COLON},

	{TT_EXCL_TEXT, TT_EXCL},
	{TT_AMP_TEXT, TT_AMP},
	{TT_BAR_TEXT, TT_BAR},

	{TT_EQEQ_TEXT, TT_EQEQ},
	{TT_EXCLEQ_TEXT, TT_EXCLEQ},
	{TT_LTEQ_TEXT, TT_LTEQ},
	{TT_GTEQ_TEXT, TT_GTEQ},

	{TT_PLUSEQ_TEXT, TT_PLUSEQ},
	{TT_MINUSEQ_TEXT, TT_MINUSEQ},
	{TT_STAREQ_TEXT, TT_STAREQ},
	{TT_SLASHEQ_TEXT, TT_SLASHEQ},
	{TT_PERCENTEQ_TEXT, TT_PERCENTEQ},
	{TT_AMPEQ_TEXT, TT_AMPEQ},
	{TT_CARETEQ_TEXT, TT_CARETEQ},
	{TT_BAREQ_TEXT, TT_BAREQ},

	{TT_PLUSPLUS_TEXT, TT_PLUSPLUS},
	{TT_MINUSMINUS_TEXT, TT_MINUSMINUS},

	{TT_COLONCOLON_TEXT, TT_COLONCOLON},

	{TT_AMPAMP_TEXT, TT_AMPAMP},
	{TT_BARBAR_TEXT, TT_BARBAR},

	{TT_LTLT_TEXT, TT_LTLT},
	{TT_GTGT_TEXT, TT_GTGT},

	{TT_DOTDOT_TEXT, TT_DOTDOT},
	{TT_STARSTAR_TEXT, TT_STARSTAR},
	{TT_LTMINUS_TEXT, TT_LTMINUS},
	{TT_EQGT_TEXT, TT_EQGT},
};
lets_map_t<lets_str_t, u_tt_t> Lexer::KEYWORDS = {
	{TT_KW_PRINT_TEXT, TT_KW_PRINT},
	{TT_KW_PUT_TEXT, TT_KW_PUT},
	{TT_KW_IF_TEXT, TT_KW_IF},
	{TT_KW_ELSE_TEXT, TT_KW_ELSE},
	{TT_KW_ELIF_TEXT, TT_KW_ELIF},
	{TT_KW_WHILE_TEXT, TT_KW_WHILE},
	{TT_KW_FOR_TEXT, TT_KW_FOR},
	{TT_KW_DO_TEXT, TT_KW_DO},
	{TT_KW_BREAK_TEXT, TT_KW_BREAK},
	{TT_KW_CONTINUE_TEXT, TT_KW_CONTINUE},
	{TT_KW_DEF_TEXT, TT_KW_DEF},
	{TT_KW_RETURN_TEXT, TT_KW_RETURN},
	{TT_KW_USE_TEXT, TT_KW_USE},
	{TT_KW_END_TEXT, TT_KW_END},
	{TT_KW_IN_TEXT, TT_KW_IN},
	{TT_KW_INCLUDE_TEXT, TT_KW_INCLUDE},
	{TT_KW_MODE_TEXT, TT_KW_MODE},
	{TT_KW_MATCH_TEXT, TT_KW_MATCH},
	{TT_KW_CASE_TEXT, TT_KW_CASE},
	{TT_KW_DEFAULT_TEXT, TT_KW_DEFAULT},
	{TT_KW_AND_TEXT, TT_KW_AND},
	{TT_KW_OR_TEXT, TT_KW_OR},
	{TT_KW_NOT_TEXT, TT_KW_NOT},
	{TT_KW_NEW_TEXT, TT_KW_NEW},
	{TT_KW_CLASS_TEXT, TT_KW_CLASS},
};

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

	if(KEYWORDS.find(this->buffer) != KEYWORDS.end()){
		add_token(KEYWORDS[this->buffer], start_row, start_col);
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
		if(!text.empty() && OPERATORS.find(text + current) == OPERATORS.end()){
			// if(!text.empty() && find (OPERATORS.begin(), OPERATORS.end(), text + current) == OPERATORS.end()){
			add_token(OPERATORS[text], text);
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

int Lexer::find_c(lets_str_t s, char c) {
	std::size_t pos = s.find(c);
	return (pos == lets_str_t::npos) ? -1 : (int)pos; 
}

void Lexer::add_token(u_tt_t tt){
	add_token(tt, "");
}

void Lexer::add_token(u_tt_t tt, size_t r, size_t c){
	add_token(tt, "", r, c);
}

void Lexer::add_token(u_tt_t tt, lets_str_t txt){
	this->tokens.push_back(Token(tt, txt, this->row, this->col));
}

void Lexer::add_token(u_tt_t tt, lets_str_t txt, size_t r, size_t c){
	this->tokens.push_back(Token(tt, txt, r, c));
}
