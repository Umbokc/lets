//
//  ex_lexer.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef exceptions__lexer_h
#define exceptions__lexer_h

#include "main.h"

class LexerException {
public:
	lets_str_t head = "Lexer error";
	size_t row = 0, col = 0;
	lets_str_t message;

	LexerException() {}

	LexerException(lets_str_t message)
		:message(std::move(message)){}

	LexerException(lets_str_t message, lets_str_t head)
		:message(std::move(message)), head(std::move(head)){}

	LexerException(lets_str_t message, size_t row, size_t col)
		:message(std::move(message)),
		row(std::move(row)), col(std::move(col)){}

	LexerException(lets_str_t message, lets_str_t head, size_t row, size_t col)
		:message(std::move(message)), head(std::move(head)),
		row(std::move(row)), col(std::move(col)){}

	lets_str_t get_message() {
		return message;
	}

	~LexerException() {}

};

#endif /* exceptions__lexer_h */
