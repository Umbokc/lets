//
//  token.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/token.hpp"
#include "../include/tokentype.h"

Token::Token(){}
Token& Token::operator=(const Token& t){return *this;}

Token::Token(const u_tt_t& tt, const lets_str_t& txt, const int& r, const int& c)
	:type(std::move(tt)), text(std::move(txt)), row(std::move(r)), col(std::move(c)){}

// type get/set
u_tt_t Token::get_type(){ return type; }
void Token::set_type(const int& type){ this->type = type; }

// test get/set
lets_str_t Token::get_text(){ return text; }
void Token::set_text(const lets_str_t& text){ this->text = text; }

// convert to string need data (token and text)
lets_str_t Token::to_s(){ 
	return (TokenTypeString[this->type] + " " + text);
}

int Token::get_row() { return row; }
int Token::get_col() { return col; }

lets_str_t Token::get_position() {
	return "[" + std::to_string(row) + ":" + std::to_string(col) + "]";
}

Token::~Token(){}
