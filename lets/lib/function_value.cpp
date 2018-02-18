//
//  lets/lib/function_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream> // for dbg
#include "../../include/lib/include_values.h"
// #include "../../include/lib/call_stack.h"
#include "../../include/exception/execute.h"
#include "../../include/exception/error.h"

FunctionValue::FunctionValue(){
	this->construct();
}

FunctionValue::FunctionValue(Function* value):value(std::move(value)){
	this->construct();
}

Value* FunctionValue::construct(){
	this->set_class_name("Function");
	// DEFAULT_METHODS_OF_CLASS()
}

Value* FunctionValue::construct(FUNCS_ARGS args){
}

bool FunctionValue::as_bool(){
	return (bool)as_number();
}

int FunctionValue::as_int(){
	return (int)as_number();
}

double FunctionValue::as_number(){
	throw ExecuteException(ExceptionsError::E_CNN_FUNC_TO_NUM);
}

long FunctionValue::as_long(){
	return (long)as_number();
}

Function* FunctionValue::get_value(){
	return value;
}

int FunctionValue::len(){
	return -1;
}

lets_str_t FunctionValue::as_string(){
	return this->value->to_s();
}

lets_str_t FunctionValue::to_s(){
	return as_string();
}

Types FunctionValue::type(){
	return Types::T_FUNCTION;
}

bool FunctionValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;
	if(dynamic_cast<FunctionValue*>(obj))
		return this->value == dynamic_cast<FunctionValue*>(obj)->value;
	
	return false;
}

int FunctionValue::compareTo(Value *obj){
	if (obj->type() == this->type()) {
		int length_compare = lets_compare(len(), dynamic_cast<FunctionValue*>(obj)->len());
		if (length_compare != 0) return length_compare;
	}
	return lets_compare(as_string(), obj->as_string());
}


Value* FunctionValue::get(Value* key){
	return this->get_prop(key);
}

void FunctionValue::set(Value* key, Value* value){
	this->set_prop(key, value);
}

FunctionValue::~FunctionValue(){}
