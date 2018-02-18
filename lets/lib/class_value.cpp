//
//  lets/lib/class_value.cpp
//  lets
//
//  Created by Dragan Stepan on 11.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include <iostream> // for dbg
#include "../../include/lib/include_values.h"
#include "../../include/exception/execute.h"
#include "../../include/exception/error.h"

ClassValue::ClassValue(){this->construct();}

ClassValue::ClassValue(Value* value):value(std::move(value)){this->construct();}

Value* ClassValue::construct(){
	this->set_class_name("Class");
	DEFAULT_METHODS_OF_CLASS()
}

Value* ClassValue::construct(FUNCS_ARGS args){
}

bool ClassValue::as_bool(){
	return (bool)as_number();
}

int ClassValue::as_int(){
	return (int)as_number();
}

double ClassValue::as_number(){
	throw ExecuteException(ExceptionsError::E_CNN_CLASS_TO_NUM);
}

long ClassValue::as_long(){
	return (long)as_number();
}

Value* ClassValue::get_value(){
	return value;
}

Value* ClassValue::get(Value* key){
	return this->get_prop(key);
}

void ClassValue::set(Value* key, Value* value){
	this->set_prop(key, value);
}

int ClassValue::len(){
	return -1;
}

lets_str_t ClassValue::as_string(){
	return this->value->as_string();
}

lets_str_t ClassValue::to_s(){
	return this->value->to_s();
}

Types ClassValue::type(){
	return Types::T_CLASS;
}

bool ClassValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;
	if(dynamic_cast<ClassValue*>(obj))
		return this->value == dynamic_cast<ClassValue*>(obj)->value;
	
	return false;
}

int ClassValue::compareTo(Value *obj){
	if (obj->type() == this->type()) {
		int length_compare = lets_compare(len(), dynamic_cast<ClassValue*>(obj)->len());
		if (length_compare != 0) return length_compare;
	}
	return lets_compare(as_string(), obj->as_string());
}

ClassValue::~ClassValue(){}
