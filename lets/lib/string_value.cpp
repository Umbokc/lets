//
//  lets/lib/string_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg
#include <cstdlib>
#include "../../include/lib/string_value.hpp"

StringValue::StringValue(){
	this->value = "";
}

StringValue::StringValue(char value){
	this->value = lets_ctos(value);
}

StringValue::StringValue(lets_str_t value){
	this->value = value;
}

bool StringValue::as_bool(){
	return this->value != "";
}

int StringValue::as_int(){
	return (int)as_number();
}

double StringValue::as_number(){
	return atof(&value[0u]);
}

long StringValue::as_long(){
	return std::stol(&value[0u], 0);
}

lets_str_t StringValue::get_c(int index){
	return lets_ctos(value[index]);
}

bool StringValue::has(Value* val){
	if (this == val) return false;
	if (this->type() != val->type()) return false;

	return (this->value.find(val->to_s()) != std::string::npos);
}

bool StringValue::has(Value* val, int index){
	if (this == val) return false;
	if (index < 0) return false;

	if (this->type() != val->type()) return false;
	auto pos = this->value.find(val->to_s());
	if(pos != std::string::npos && int(pos) == index){
		return true;
	}

	return false;
}

int StringValue::len(){
	return (int)value.length();
}

lets_str_t StringValue::as_string(){
	return value;
}

lets_str_t StringValue::to_s(){
	return as_string();
}

Types StringValue::type(){
	return Types::T_STRING;
}

bool StringValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;
	char c = this->value.compare(dynamic_cast<StringValue*>(obj)->value);
	return (int)c == 0;
}

int StringValue::compareTo(Value *obj) {
	if (obj->type() == this->type()) {
		return this->value.compare(dynamic_cast<StringValue*>(obj)->value);
	}
	return this->value.compare(obj->as_string());
}

StringValue::~StringValue(){}

// lets_str_t StringValue::lets_ctos(char a) {
// 	lets_str_t s = "";
// 	return s + a;
// }
