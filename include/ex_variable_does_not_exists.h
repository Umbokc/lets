//
//  ex_variable_does_not_exists.h
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ex_variable_does_not_exists_h
#define ex_variable_does_not_exists_h

#include "ex_execute.h"

class VariableDoesNotExistsException : public ExecuteException{
private:
	lets_str_t variable;
public:

	VariableDoesNotExistsException(lets_str_t& variable):variable(std::move(variable)){
		this->message = "Variable " + this->variable + " does not exists";
	}

	lets_str_t get_variable(){ return this->variable; }

};

#endif /* ex_variable_does_not_exists_h */
