//
//  lets/lib/number_value->cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../../include/lib/include_values.h"
#include "../../include/tools.hpp"
#include "../../include/exception/execute.h"

NumberValue::NumberValue(){
	this->construct();
}

NumberValue::NumberValue(int value){
	this->value = new Number(value);
	this->construct();
}

NumberValue::NumberValue(double value){
	this->value = new Number(value);
	this->construct();
}

NumberValue::NumberValue(long value){
	this->value = new Number(value);
	this->construct();
}

NumberValue::NumberValue(Number* value):value(std::move(value)){this->construct();}

Value* NumberValue::construct(){
	this->set_class_name("Number");
	DEFAULT_METHODS_OF_CLASS()
}

Value* NumberValue::construct(FUNCS_ARGS args){
	if(args.size() == 0){
		value = new Number(0);
	} else {
		try{
			if(args.at(0)->type() == T_NUMBER){
				value = dynamic_cast<NumberValue*>(args.at(0))->get_value();
			} else {
				value = NS_Tools::create_number(args.at(0)->as_string());
			}
		} catch(const std::exception& e){
			throw ExecuteException(e.what());
		}
	}

	return this;
}

Number* NumberValue::get_value(){
	return this->value;
}

bool NumberValue::as_bool(){
	return this->value->as_int() != 0;
}

int NumberValue::as_int(){
	return this->value->as_int();
}

double NumberValue::as_number(){
	return this->value->as_double();
}

long NumberValue::as_long(){
	return this->value->as_long();
}

int NumberValue::len(){
	return -1;
}

Types NumberValue::type(){
	return T_NUMBER;
}

lets_str_t NumberValue::as_string(){
	return this->value->as_string();
}

lets_str_t NumberValue::to_s(){
	return this->value->to_s();
}

bool NumberValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;

	if(!dynamic_cast<NumberValue*>(obj)) return false;

	Number* other = dynamic_cast<NumberValue*>(obj)->value;

	if (this->value->is_double() || other->is_double()) {
		return (this->value->as_double() == other->as_double());
	}

	if (this->value->is_long() || other->is_long()) {
		return (this->value->as_long() == other->as_long());
	}

	return (this->value->as_int() == other->as_int());
}

int NumberValue::compareTo(Value *obj) {
	if (obj->type() == this->type()) {
		Number* other = dynamic_cast<NumberValue*>(obj)->value;

		if (this->value->is_double() || other->is_double())
			return lets_compare(this->value->as_double(), other->as_double());

		if (this->value->is_long() || other->is_long())
			return lets_compare(this->value->as_long(), other->as_long());

		return lets_compare(this->value->as_int(), other->as_int());
	}

	return lets_compare(as_string(), obj->as_string());
}

Value* NumberValue::get(Value* key){
	return this->get_prop(key);
}

void NumberValue::set(Value* key, Value* value){
	this->set_prop(key, value);
}

NumberValue::~NumberValue(){}

NumberValue* NumberValue::ZERO = new NumberValue(0);
NumberValue* NumberValue::ONE = new NumberValue(1);
NumberValue* NumberValue::NEGATE_ONE = new NumberValue(-1);
