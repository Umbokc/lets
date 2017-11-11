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
protected:
	lets_str_t message;
	int row, col;
public:

	LexerException() {}

	LexerException(lets_str_t message) :message(std::move(message)) {
		col = row = -2;
	}

	LexerException(lets_str_t message, int r, int c)
		:message(std::move(message)), row(std::move(r)), col(std::move(c)) {}

	lets_str_t get_message() {
		if (row >= 0 && col >= 0) {
			return "Lexer error [" + std::to_string(this->row) + ":" + std::to_string(this->col) + "]: " + message;
		}
		return message;
	}

	~LexerException() {}

};

#endif /* exceptions__lexer_h */
