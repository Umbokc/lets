//
//  include/exception/variable_does_not_exists.h
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__exception__variable_does_not_exists_h
#define include__exception__variable_does_not_exists_h

#include "execute.h"

class VariableDoesNotExistsException : public ExecuteException{
private:
	lets_str_t variable;
public:

  VariableDoesNotExistsException(lets_str_t& variable):variable(std::move(variable)){
    this->message = "Variable " + this->variable + " does not exists";
  }

	VariableDoesNotExistsException(lets_str_t& variable, size_t row, size_t col):ExecuteException(row, col), variable(std::move(variable)){
		this->message = "Variable " + this->variable + " does not exists";
	}

	lets_str_t get_variable(){ return this->variable; }

};

#endif /* include__exception__variable_does_not_exists_h */
