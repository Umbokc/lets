//
//  token.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//
// #include <iostream> // for dbg
#include "../include/token.hpp"
#include "../include/tokentype.h";

Token::Token(){}
Token& Token::operator=(const Token& t){return *this;}

Token::Token(u_tt_t tt, u_tt_t k, u_tt_t o, lets_str_t txt, size_t r, size_t c)
	:type(std::move(tt)), 
	kw(std::move(k)), op(std::move(o)),
	text(txt),
	row(std::move(r)), col(std::move(c)){}

u_tt_t Token::get_kw(){ return this->kw; }
void Token::set_kw(const u_tt_t& kw){ this->kw = kw; }

u_tt_t Token::get_op(){ return this->op; }
void Token::set_op(const u_tt_t& op){ this->op = op; }

u_tt_t Token::get_type(){ return this->type; }
void Token::set_type(const u_tt_t& type){ this->type = type; }

lets_str_t Token::get_text(){ return this->text; }
void Token::set_text(const lets_str_t& text){ this->text = text; }

lets_str_t Token::to_s(){
	return TOKEN_TO_STRING(this->type, this->text);
}

size_t Token::get_row() { return this->row; }
void Token::set_row(size_t r) { this->row = r; }
size_t Token::get_col() { return this->col; }
void Token::set_col(size_t c) { this->col = c; }

lets_str_t Token::get_position() {
	return "[" + std::to_string(row) + ":" + std::to_string(col) + "]";
}

Token::~Token(){}
