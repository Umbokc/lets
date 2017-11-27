//
//  e_unary_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_unary_expr.hpp"
#include "../include/accessible.h"
#include "../include/l_bool_value.hpp"
#include "../include/l_number_value.hpp"
#include "../include/l_string_value.hpp"
#include "../include/l_array_value.hpp"
#include "../include/ex_execute.h"
#include "../include/tools.hpp"


const lets_str_t UnaryExpression::OperatorString[7] = {
	"++",
	"--",
	"++",
	"--",
	"-",
	// Boolean
	"!",
	// Bitwise
	"~",
};

UnaryExpression::UnaryExpression(Operator operation, Expression* expr):
operation(std::move(operation)), expr(std::move(expr)){}

void UnaryExpression::execute(){
	eval();
}

Value *UnaryExpression::eval() {
	Value *value = expr->eval();
	switch (operation) {
		case Operator::INCREMENT_PREFIX:
		if(dynamic_cast<Accessible*>(expr)){
			return dynamic_cast<Accessible*>(expr)->set(UE_increment(value));
		}
		return UE_increment(value);
		case Operator::INCREMENT_POSTFIX:
		if(dynamic_cast<Accessible*>(expr)){
			dynamic_cast<Accessible*>(expr)->set(UE_increment(value));
			return value;
		}
		return UE_increment(value);
		case Operator::DECREMENT_PREFIX:
		if(dynamic_cast<Accessible*>(expr)){
			return dynamic_cast<Accessible*>(expr)->set(UE_decrement(value));
		}
		return UE_decrement(value);
		case Operator::DECREMENT_POSTFIX:
		if(dynamic_cast<Accessible*>(expr)){
			dynamic_cast<Accessible*>(expr)->set(UE_decrement(value));
			return value;
		}
		return UE_decrement(value);
		case Operator::NEGATE:
		return UE_negate(value);
		case Operator::NOT:
		return UE_not(value);
		case Operator::COMPLEMENT:
		return UE_complement(value);
		default:
		throw ExecuteException("Operation Is Not Supported");
	}
}

Value *UnaryExpression::UE_increment(Value *value){
	if(value->type() == Types::T_STRING) {
		lets_str_t newval = value->as_string();
		if(newval == "") return NumberValue::ONE;
		newval.back() = ++newval.back();
		return new StringValue(newval);
	}
	
	return new NumberValue(value->as_number() + 1);
}

Value *UnaryExpression::UE_decrement(Value *value){
	if(value->type() == Types::T_STRING) {
		lets_str_t newval = value->as_string();
		if(newval == "") return NumberValue::NEGATE_ONE;
		newval.back() = --newval.back();
		return new StringValue(newval);
	}
	return new NumberValue(value->as_number() - 1);
}

Value *UnaryExpression::UE_complement(Value *value){
	return new NumberValue(~(int)value->as_number());
}

Value *UnaryExpression::UE_negate(Value *value){
	if(value->type() == Types::T_NUMBER){
		
		return new NumberValue(-value->as_number());
		
	} else if(value->type() == Types::T_STRING){
		
		return new StringValue(reverse(value->as_string()));
		
	} else if(value->type() == Types::T_ARRAY){
		
		auto new_arr = dynamic_cast<ArrayValue*>(value)->get_all();
		reverse(std::begin(new_arr), std::end(new_arr));
		return new ArrayValue(new_arr);
		
	}
	
	return NumberValue::ZERO;
}

Value *UnaryExpression::UE_not(Value *value){
	if(value->type() == Types::T_BOOL){
		return new BoolValue(!value->as_bool());
	} else if(value->type() == Types::T_NUMBER){
		return new BoolValue(value->as_number() == 0);
	} else if(value->type() == Types::T_STRING){
		return new BoolValue(value->as_string() == "");
	}
	return BoolValue::FALSE;
}


lets_str_t UnaryExpression::to_s(){
	return NS_Tools::string_format(
		"[%s %s]",
		OperatorString[operation].c_str(),
		expr->to_s().c_str()
	);
}

UnaryExpression::~UnaryExpression(){
	// delete[] expr;
}

lets_str_t UnaryExpression::reverse(const lets_str_t& the) {
	lets_str_t newstr("");
	for (int i = (int)(the.length() - 1); i >= 0; --i) {
		newstr += the[i];
	}
	return newstr;
}

