//
//  ex_parse.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef exceptions__parse_h
#define exceptions__parse_h

#include <string>
#include "main.h"

class ParseException {
protected:
	lets_str_t message;
public:
	lets_str_t head = "Error";
	size_t row = 0, col = 0;

	ParseException(){}

	ParseException(lets_str_t message)
		:message(std::move(message)){}

	ParseException(lets_str_t message, lets_str_t head)
		:message(std::move(message)), head(std::move(head)){}

	ParseException(lets_str_t message, lets_str_t head, size_t row, size_t col)
		:message(std::move(message)), head(std::move(head)),
		row(std::move(row)), col(std::move(col)){}

	lets_str_t get_message(){ return message; }

	~ParseException(){}

};

#endif /* exceptions__parse_h */
