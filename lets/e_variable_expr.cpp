//
//  e_variable_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_variable_expr.hpp"
#include "../include/l_variables.h"
#include "../include/ex_variable_does_not_exists.h"

VariableExpression::VariableExpression(lets_str_t name):name(std::move(name)){}

Value* VariableExpression::eval(){
    return get();
}

Value* VariableExpression::get(){
    if(!Variables::is_exists_all(name)) throw VariableDoesNotExistsException(name);
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
