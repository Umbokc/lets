#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <locale>
#include <fstream>

std::string appendCharToString(std::string const & s, char a);
std::string strToLower (std::string str);
std::string dtos (double d);
void debug (std::string const & s);
void debugc (char c);

#include "lib/Value.h"
#include "lib/StringValue.h"
#include "lib/NumberValue.h"
#include "lib/Variables.h"

#include "parser/TokenType.h"
#include "parser/Token.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"

std::string appendCharToString(std::string const & s, char a) {
	return s + a;
}

void debugc (char c){
	cout << c;
}

void debug (std::string const & s){
	cout << s;
}

std::string strToLower (std::string str) {
	std::locale loc;
	std::string str_new;

	for(auto elem : str){
		str_new = appendCharToString(str_new, std::tolower(elem,loc));
	}

	return str_new;
}

std::string dtos (double d) {
	std::ostringstream strs;
	strs << d;
	return strs.str();
}
#endif