//
//  lets/utils/minifier.cpp
//  lets
//
//  Created by Dragan Stepan on 24.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/utils/minifier.hpp"
#include "../../include/tools.hpp"

Minifier::Minifier(){}

Minifier::Minifier(lets_str_t input) {
	this->input = input;
	this->length = input.length();
	this->minified_code = "";
}

Minifier::~Minifier(){}

lets_str_t Minifier::minify(lets_str_t input) {
	return (Minifier(input)).minify();
}

lets_str_t Minifier::minify() {
	char current;
	for(int i = 0; i < length; i++){
		current = input.at(i);
		switch (current) {
			case '#':
				while(input.at(i) != '\n') i++;
				break;
			case '\n':
				if(this->minified_code.back() != ' ' && this->minified_code.back() != '\n')
					this->minified_code.push_back(' ');
				break;
			case '\t':
				if(this->minified_code.back() != ' ' && this->minified_code.back() != '\n')
					this->minified_code.push_back(' ');
				break;
			case ' ':
				if(this->minified_code.back() != ' ' && this->minified_code.back() != '\n')
					this->minified_code.push_back(' ');
				break;
			case '"':
				if(peek(i+1) == '"' && peek(i+2) == '"'){
					i++; i++; i++;
					while(true){
						current = peek(++i);
						if((current == '"' && peek(i+1) == '"' && peek(i+2) == '"') or current == '\0') break;
					}
					i++; i++; i++;
					break;
				}
			default:
				this->minified_code.push_back(current);
				break;
		}
	}

	NS_Tools::trim(this->minified_code);
	return this->minified_code;
}

char Minifier::peek(lets_str_t::size_type pos) {
	if (pos >= this->length) return '\0';
	return this->input.at(pos);
}