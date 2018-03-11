//
//  lets/expressions/class_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 11.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include <iostream>
#include "../../include/expressions/class_expr.hpp"
#include "../../include/tools.hpp"
#include "../../include/lib/classes.hpp"
#include "../../include/lib/variables.hpp"
// #include "../../include/lib/call_stack.h"
#include "../../include/lib/string_value.hpp"
#include "../../include/exception/variable_does_not_exists.h"
#include "../../include/exception/error.h"

ClassExpression::ClassExpression(){}
ClassExpression::~ClassExpression(){}

ClassExpression::ClassExpression(Expression* class_expr):
	class_expr(std::move(class_expr)){}

void ClassExpression::add_arguments(Expression *arg){
	arguments.push_back(arg);
}

void ClassExpression::execute(){
	try{
		eval();
	} catch(ExecuteException& e){
		e.row = this->get_position_row();
		e.col = this->get_position_col();
		throw e;
	}
}

Value *ClassExpression::eval(){
	int size = (int)this->arguments.size();
	FUNCS_ARGS values;
	values.reserve(size);

	for (Expression *argument : this->arguments){
		values.push_back(argument->eval());
	}

	Value *cl = consume_class(class_expr);
	// CallStack::enter(class_expr->to_s(), cl);
	Value* result = cl->construct(values);
	// CallStack::exit();
	return result;
}

lets_str_t ClassExpression::name_to_s(){
	return this->class_expr->to_s();
}

lets_str_t ClassExpression::args_to_s(){
	return NS_Tools::vector_to_s(this->arguments, ", ") ;
}

lets_str_t ClassExpression::to_s(){
	return "new " + name_to_s() + "( " + args_to_s() + " )";
}

Value* ClassExpression::consume_class(Expression *expr){

	try{
		Value* value = expr->eval();
		// if(value->type() == Types::T_CLASS)
			return value;
		// return get_class(value->as_string());
	} catch (VariableDoesNotExistsException& e) {
		return get_class(e.get_variable());
	}
}

Value* ClassExpression::get_class(lets_str_t key){

	if(Classes::is_exists(key)) return Classes::get(key);

	if(Variables::is_exists(key)){
		return Variables::get(key);
	}

	throw ExecuteException(NS_Tools::string_format(ExceptionsError::E_UNKNOWN_CLASS, key.c_str()), this->get_position_row(), this->get_position_col());
}