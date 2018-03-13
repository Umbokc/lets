//
//  lets/expressions/binary_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream> // for dbg
#include <cmath>
#include "../../include/tools.hpp"
#include "../../include/expressions/binary_expr.hpp"

#include "../../include/expressions/array_expr.hpp"
#include "../../include/expressions/container_access_expr.hpp"
#include "../../include/expressions/variable_expr.hpp"
#include "../../include/expressions/value_expr.hpp"

#include "../../include/exception/execute.h"
#include "../../include/lib/array_value.hpp"
#include "../../include/lib/string_value.hpp"
#include "../../include/lib/null_value.hpp"
#include "../../include/exception/operation_is_not_supported.h"


BinaryExpression::BinaryExpression(NS_Binary::Operator operation, Expression* expr1, Expression* expr2):
operation(std::move(operation)), expr1(std::move(expr1)), expr2(std::move(expr2)){}

Value * BinaryExpression::eval(){
	Value *value1, *value2;
	LETS_TRY_EXCEPTION_EXECUTE_START()
	value1 = expr1->eval();
	LETS_TRY_EXCEPTION_EXECUTE_END_POS(expr1)
	LETS_TRY_EXCEPTION_EXECUTE_START()
	value2 = expr2->eval();
	LETS_TRY_EXCEPTION_EXECUTE_END_POS(expr2)

	try{
		return eval(value1, value2);
	} catch (std::exception& e){
		throw e;
	}
}

lets_str_t BinaryExpression::to_s(){
	return NS_Tools::string_format(
		"%s %s %s",
		expr1->to_s().c_str(),
		NS_Binary::OperatorString[operation].c_str(),
		expr2->to_s().c_str()
	);
}

BinaryExpression::~BinaryExpression(){}

Value *BinaryExpression::eval(Value *value1, Value *value2){
	try{
		switch (operation) {
			case NS_Binary::ADD: return bin_op_add(value1, value2);
			case NS_Binary::SUBTRACT: return bin_op_subtract(value1, value2);
			case NS_Binary::MULTIPLY: return bin_op_multiply(value1, value2);
			case NS_Binary::DIVIDE: return bin_op_divide(value1, value2);
			case NS_Binary::REMAINDER: return bin_op_remainder(value1, value2);
			case NS_Binary::AND: return bin_op_and(value1, value2);
			case NS_Binary::OR: return bin_op_or(value1, value2);
			case NS_Binary::XOR: return bin_op_xor(value1, value2);
			case NS_Binary::LSHIFT: return bin_op_lshift(value1, value2);
			case NS_Binary::RSHIFT: return bin_op_rshift(value1, value2);
			case NS_Binary::POWER: return bin_op_power(value1, value2);
			default:
			operation_is_not_supported();
		}
	} catch(ExecuteException& pe){
		throw ExecuteException(pe.get_message(), this->get_position_row(), this->get_position_col());
	}
	return NullValue::THE_NULL;
}

Value *BinaryExpression::bin_op_add(Value *value1, Value *value2) {

	switch (value1->type()) {
		case Types::T_NUMBER:
		return bin_op_add(dynamic_cast<NumberValue *>(value1), value2);
		case Types::T_ARRAY:
		if(value2->type() == Types::T_ARRAY){
			return NS_ArrayValue::merge(
				dynamic_cast<ArrayValue *>(value1),
				dynamic_cast<ArrayValue *>(value2)
				);
		} else if(value2->type() == Types::T_STRING){
			return new StringValue(value1->as_string() + value2->as_string());
		}
		throw ExecuteException("Cannot merge non array value to array");
		case Types::T_STRING:
		default:
		return new StringValue(value1->as_string() + value2->as_string());
	}

}

Value *BinaryExpression::bin_op_add(NumberValue *value1, Value *value2) {
	switch (value2->type()) {
		case Types::T_STRING:{
			return new StringValue(
				value1->as_string() + value2->as_string()
				);
		}
		case Types::T_NUMBER:
		default:
		return new NumberValue(value1->as_number() + value2->as_number());
	}
}

Value *BinaryExpression::bin_op_subtract(Value *value1, Value *value2) {
	return new NumberValue(value1->as_number() - value2->as_number());
}

Value *BinaryExpression::bin_op_multiply(Value *value1, Value *value2) {

	switch (value1->type()) {
		case Types::T_NUMBER:{
			return new NumberValue(value1->as_number() * value2->as_number());
		}
		case Types::T_ARRAY:{
			int iterat = value2->as_int();

			lets_vector_t<Value *> temparr;
			lets_vector_t<Value *> arr = dynamic_cast<ArrayValue *>(value1)->get_all();

			temparr.reserve(arr.size() * iterat);

			for (int i = 0; i < iterat; ++i) {
				temparr.insert(temparr.end(), arr.begin(), arr.end());
			}

			return new ArrayValue(temparr);
		}
		case Types::T_STRING:{

			int iterat = value2->as_int();
			lets_str_t str = value1->as_string();
			lets_str_t result("");
			for (int i = 0; i < iterat; ++i){
				result += str;
			}
			return new StringValue(result);
		}
		default:
		operation_is_not_supported();
	}

	return NullValue::THE_NULL;
}

Value *BinaryExpression::bin_op_divide(Value *value1, Value *value2) {
	if(value2->as_number() == 0)
		// throw ExecuteException("Division by zero is undefined");
		return NullValue::THE_NULL;
	else
		return new NumberValue(value1->as_number() / value2->as_number());
}

Value *BinaryExpression::bin_op_remainder(Value *value1, Value *value2) {
	return new NumberValue(value1->as_int() % value2->as_int());
}

Value *BinaryExpression::bin_op_and(Value *value1, Value *value2) {
	return new NumberValue(value1->as_int() & value2->as_int());
}

Value *BinaryExpression::bin_op_or(Value *value1, Value *value2) {
	return new NumberValue(value1->as_int() | value2->as_int());
}

Value *BinaryExpression::bin_op_xor(Value *value1, Value *value2) {
	return new NumberValue(value1->as_int() ^ value2->as_int());
}

Value *BinaryExpression::bin_op_lshift(Value *value1, Value *value2) {
	switch (value1->type()) {
		case Types::T_NUMBER:
		return new NumberValue(value1->as_int() << value2->as_int());
		case Types::T_ARRAY:
		dynamic_cast<ArrayValue *>(value1)->add(value2);
		return value1;
		default:
		operation_is_not_supported();
	}

	return NullValue::THE_NULL;
}

Value *BinaryExpression::bin_op_rshift(Value *value1, Value *value2) {
	// if(value1->type() == Types::T_ARRAY ){
	// 	dynamic_cast<ArrayValue *>(value1)->add_forward(value2);
	// 		if(value2->type() == Types::T_ARRAY){
	// 			dynamic_cast<ArrayValue *>(value1)->add_forward(value2);
	// 			return ArrayValue::merge(
	// 				dynamic_cast<ArrayValue *>(value2),
	// 				dynamic_cast<ArrayValue *>(value1)
	// 			);
	// 		} else {
	// 			throw ExecuteException("Cannot add element to non array value");
	// 		}
	// }

	if(value2->type() == Types::T_ARRAY){
		dynamic_cast<ArrayValue *>(value2)->add_forward(value1);
		return value2;
	}

	return new NumberValue(value1->as_int() >> value2->as_int());
}

Value *BinaryExpression::bin_op_power(Value *value1, Value *value2) {
	if(value1->type() == Types::T_NUMBER and value2->type() == Types::T_NUMBER){

		Number* val1 = dynamic_cast<NumberValue*>(value1)->get_value();
		Number* val2 = dynamic_cast<NumberValue*>(value2)->get_value();


		auto res = pow(
			val1->is_long() ? val1->as_long() : val1->is_double() ? val1->as_double() : val1->as_int(),
			val2->is_long() ? val2->as_long() : val2->is_double() ? val2->as_double() : val2->as_int()
			);

		return new NumberValue(res);

	} else {
		throw ExecuteException("Expected numeric values for exponentiation");
	}
}

void BinaryExpression::operation_is_not_supported(){
	throw OperationIsNotSupportedException(
		NS_Binary::OperatorString[operation]
		);
}
