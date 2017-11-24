//
//  ex_execute.h
//  lets
//
//  Created by Dragan Stepan on 16.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef exceptions__ex_execute_h
#define exceptions__ex_execute_h

#include <string>
#include "main.h"

class ExecuteException {
protected:
	lets_str_t message;
public:
	lets_str_t head = "Error";
	lets_str_t file_name = "";
	size_t row = 0, col = 0;

	ExecuteException(){}

	ExecuteException(lets_str_t message)
		:message(std::move(message)){}

	ExecuteException(lets_str_t message, lets_str_t head)
		:message(std::move(message)), head(std::move(head)){}

	ExecuteException(lets_str_t message, lets_str_t head, size_t row, size_t col)
		:message(std::move(message)), head(std::move(head)),
		row(std::move(row)), col(std::move(col)){}

	ExecuteException(lets_str_t message, size_t row, size_t col)
		:message(std::move(message)),
		row(std::move(row)), col(std::move(col)){}

	ExecuteException(lets_str_t message, size_t row, size_t col, lets_str_t file)
		:message(std::move(message)),
		row(std::move(row)), col(std::move(col)),
		file_name(std::move(file)){}

	lets_str_t get_message(){ return message; }

	~ExecuteException(){}

};

#endif /* exceptions__ex_execute_h */
