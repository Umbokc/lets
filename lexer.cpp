#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"

std::vector<Token> Lexer::tokenize(){

	while (this->pos < this->length) {
		char current = peek(0);
		if(isdigit(current)) tokenize_number();
		else if(isalpha(current, std::locale())) tokenize_word();
		else if( current == '"') tokenize_text_double_quote();
		else if( current == '\'') tokenize_text_single_quote();
		else if( current == '#') tokenize_comment();
		else if (func::find_c(NS_Lexer::OPERATORS_CHARS, current) != -1) 
			tokenize_operator();
		else
			next();
	}

	return this->tokens;
}

void Lexer::tokenize_number() {

	clear_buffer();
	char current = peek(0);
	
	bool is_octal = (current == '0');
	
	if(is_octal && look_char(1, 'x')){
		tokenize_hex_number();
		return;
	}
	if(is_octal && look_char(1, 'b')){
		tokenize_binary_number();
		return;
	}

	while (true) {

		if(current == '.') {
			if(func::find_c(this->buffer, '.') != -1 || is_octal) lexer_error(ExceptionsError::L_INVALID_FLOAT);
		} else if(!isdigit(current)){
			break;
		}

		this->buffer.push_back(current);
		current = next();
	}

	if(is_octal){
		add_token(TokenType::TT_OCTAL_NUMBER, this->buffer);
	}	else {
		add_token(TokenType::TT_NUMBER, this->buffer);
	}
}

void Lexer::tokenize_hex_number() {
	
	clear_buffer();
	next(); 
	next();

	char current = peek(0);

	while (is_hex_number(current) != -1) {
		this->buffer.push_back(current);
		current = next();
	}

	add_token(TokenType::TT_HEX_NUMBER, this->buffer);
}

int Lexer::is_hex_number(char c){
	return func::find_c("0123456789abcdef", tolower(c, std::locale()));
}

void Lexer::tokenize_binary_number() {

	next(); 
	next();
	clear_buffer();

	char current = peek(0);
	std::string cur_s;
	while (true) {
		cur_s = current;
		// cur_s.push_back(current);
		if(std::regex_match(cur_s, std::regex("^[01]+$")) == 0)
			break;

		this->buffer.push_back(current);
		current = next();
	}

	add_token(TokenType::TT_BINARY_NUMBER, this->buffer);
}

void Lexer::tokenize_word() {
	
	clear_buffer();
	char current = peek(0);
	while (true) {
		if(!(isdigit(current) || isalpha(current, std::locale())) 
				&& (current != '_') && (current != '$')){
			break;
		}

		this->buffer.push_back(current);
		current = next();
	}

	if(NS_Lexer::KEYWORDS.find(this->buffer) != NS_Lexer::KEYWORDS.end()){
		add_token(NS_Lexer::KEYWORDS[this->buffer]);
	} else {
		add_token(TokenType::TT_WORD, this->buffer);
	}
}

void Lexer::tokenize_text_double_quote() {

	next();
	clear_buffer();

	char current = peek(0);

	if(peek(0) == '"' && peek(1) == '"'){
		next(); next();
		tokenize_multiline_comment();
		return;
	}

	while (true) {
		
		if(current == '\\'){
			current = next();
			switch (current) {
				case '\\': current = next(); this->buffer.push_back('\\'); continue;
				case '"': current = next(); this->buffer.push_back('\"'); continue;
				case 'n': current = next(); this->buffer.push_back('\n'); continue;
				case 't': current = next(); this->buffer.push_back('\t'); continue;
				case 'r': current = next(); this->buffer.push_back('\r'); continue;
				case '0': current = next(); this->buffer.push_back('\0'); continue;
			}
			this->buffer.push_back('\\');
			continue;
		}

		if(current == '"') break;
		if (current == '\0') lexer_error(ExceptionsError::L_REACHED_EOF);
		this->buffer.push_back(current);
		current = next();
	}

	next();

	add_token(TokenType::TT_TEXT , this->buffer);
}

void Lexer::tokenize_text_single_quote() {

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
		if (current == '\0') lexer_error(ExceptionsError::L_REACHED_EOF);
		this->buffer.push_back(current);
		current = next();
	}

	next();

	add_token(TokenType::TT_TEXT, this->buffer);
}

void Lexer::tokenize_operator() {
	
	char current = peek(0);
	std::string text;
	clear_buffer();

	while (true) {
		text = this->buffer;
		if(!text.empty() && NS_Lexer::OPERATORS.find(text + current) == NS_Lexer::OPERATORS.end()){
			add_token(NS_Lexer::OPERATORS[text], text);
			return;
		}

		this->buffer.push_back(current);
		current = next();
	}
}

void Lexer::tokenize_comment(){
	next();
	char current = peek(0);
	while (current != '\r' && current != '\n' && current != '\0') {
		current = next();
	}	
}
void Lexer::tokenize_multiline_comment(){
	char current = peek(0);
	while (true) {
		if(current == '\0') lexer_error(ExceptionsError::L_MISS_CLOSE_TAG);
		if(current == '"' && look_char(1, '"') && look_char(2, '"')) break;
		current = next();
	}
	next();
	next();
}

bool Lexer::look_char(int rpos, char chr){
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

char Lexer::peek(int rpos){
	int position = this->pos + rpos;
	if(position >= this->length) return '\0';
	return this->input[position];
}

void Lexer::clear_buffer(){
	buffer = "";
}

void Lexer::add_token(TokenType tt){
	add_token(tt, "");
}

void Lexer::add_token(TokenType tt, std::string txt){
	this->tokens.push_back(Token(tt, txt, this->row, this->col));
}

// bool Lexer::map_key_exists(std::map<std::string, TokenType>& the_map, std::string key){
// 	return (the_map.find(key) == the_map.end());
// }

void Lexer::lexer_error(std::string mess){
	std::cout << "Lexer error ["  << std::to_string(row) << ":" << std::to_string(col) << "]: " << mess << std::endl;
	exit(1);
}
#endif