//
//  lets/expressions/variable_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/variable_expr.hpp"
#include "../../include/lib/variables.hpp"
#include "../../include/exception/variable_does_not_exists.h"

VariableExpression::VariableExpression(lets_str_t name):name(std::move(name)){}

Value* VariableExpression::eval(){
	return get();
}

Value* VariableExpression::get(){
	if(!Variables::is_exists_all(name))
		throw VariableDoesNotExistsException(name, get_position_row(), get_position_col());
	return Variables::get(name);
}

Value* VariableExpression::set(Value* value){
	Variables::set(name, value);
	return value;
}

lets_str_t VariableExpression::to_s(){
	return name;
}

VariableExpression::~VariableExpression(){}
