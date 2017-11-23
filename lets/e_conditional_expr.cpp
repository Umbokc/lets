//
//  e_conditional_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//
#include <iostream> // for dbg
#include "../include/e_conditional_expr.hpp"
#include "../include/ex_execute.h"
#include "../include/tools.hpp"

const lets_str_t ConditionalExpression::OperatorString[8] =  { "==", "!=", "<", "<=", ">", ">=", "&&", "||" };

ConditionalExpression::ConditionalExpression(
	ConditionalExpression::Operator operation, Expression* expr1, Expression* expr2):
	operation(std::move(operation)), expr1(std::move(expr1)), expr2(std::move(expr2)){}

Value* ConditionalExpression::eval(){
	Value* value1;
	Value* value2;
	double number1, number2;
	bool result;

	value1 = this->expr1->eval();

	if(this->operation == ConditionalExpression::AND)
		return new NumberValue((value1->as_bool()) ? this->expr2->eval()->as_bool() : false);
	if(this->operation == ConditionalExpression::OR)
		return new NumberValue((value1->as_bool()) ? true : this->expr2->eval()->as_bool());

	value2 = this->expr2->eval();

	if(value1->type() == Types::T_STRING){
		number1 = int(value1->as_string() != value2->as_string());
		number2 = 0;
	} else {
		number1 = value1->as_number();
		number2 = value2->as_number();
	}

	switch(this->operation){
		case ConditionalExpression::LT : result = (number1 < number2); break;
		case ConditionalExpression::LTEQ : result = (number1 <= number2); break;
		case ConditionalExpression::GT : result = (number1 > number2); break;
		case ConditionalExpression::GTEQ : result = (number1 >= number2); break;
		case ConditionalExpression::NOT_EQUALS : result = (number1 != number2); break;
		case ConditionalExpression::EQUALS : result = (number1 == number2); break;
		default:
			throw ExecuteException("Operation is not supported");
	}

	return new NumberValue(result);
}

lets_str_t ConditionalExpression::to_s(){
	return NS_Tools::string_format("[%s %s %s]",
		this->expr1->to_s().c_str(),
		ConditionalExpression::OperatorString[this->operation].c_str(),
		this->expr2->to_s().c_str()
	);
}


ConditionalExpression::~ConditionalExpression(){
}
