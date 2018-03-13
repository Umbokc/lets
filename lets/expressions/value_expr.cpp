//
//  lets/expressions/value_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/value_expr.hpp"
#include "../../include/lib/number_value.hpp"
#include "../../include/lib/string_value.hpp"
#include "../../include/lib/function_value.hpp"

ValueExpression::ValueExpression(){}

ValueExpression::ValueExpression(int value){
	this->value = new NumberValue(value);
}

ValueExpression::ValueExpression(double value){
	this->value = new NumberValue(value);
}

ValueExpression::ValueExpression(long value){
	this->value = new NumberValue(value);
}

ValueExpression::ValueExpression(Number* value){
	this->value = new NumberValue(value);
}

ValueExpression::ValueExpression(lets_str_t value){
	this->value = new StringValue(value);
}

ValueExpression::ValueExpression(Function *value){
	this->value = new FunctionValue(value);
}

ValueExpression::ValueExpression(Value *value):value(std::move(value)){}

Value *ValueExpression::eval(){
	LETS_TRY_EXCEPTION_EXECUTE_START()
	return value;
	LETS_TRY_EXCEPTION_EXECUTE_END()
}

lets_str_t ValueExpression::to_s(){
	return value->as_string();
}

ValueExpression::~ValueExpression(){}
