//
//  lets/lib/string_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg
#include <cstdlib>
#include "../../include/lib/include_values.h"

#define UPDATE_LEN() this->define_prop("len", Variable(new NumberValue(this->len()), false, true));

StringValue::StringValue(){
	this->value = "";
	this->construct();
}

StringValue::StringValue(char value){
	this->value = lets_ctos(value);
	this->construct();
}

StringValue::StringValue(lets_str_t value){
	this->value = value;
	this->construct();
}

Value* StringValue::construct(){
	this->set_class_name("String");
	DEFAULT_METHODS_OF_CLASS()

	ADD_METHOD_TO_CLASS(String, "reverse", Reverse, {
		std::reverse(std::begin(self->value), std::end(self->value));
		return self;
	}, "")

		ADD_METHOD_TO_CLASS(String, "is_empty", Is_empty, {
		return self->value.empty() ? BoolValue::TRUE : BoolValue::FALSE;
	}, "")

	ADD_METHOD_TO_CLASS(String, "has", Has, {
		if(args.size() == 0) throw ExecuteException("Method "+self->get_class_name()+".has(arg*, pos = null) one args expected");
		if(args.size() == 2){
			return self->has(args.at(0), args.at(1)->as_int()) ? BoolValue::TRUE : BoolValue::FALSE;
		}
		return self->has(args.at(0)) ? BoolValue::TRUE : BoolValue::FALSE;
	}, "arg*, pos = null")

	ADD_METHOD_TO_CLASS(String, "push", Push, {
		if(args.size() == 0) throw ExecuteException("Method "+self->get_class_name()+".push(arg*) one args expected");
		return new StringValue(self->value.append(args.at(0)->as_string()));
	}, "arg*")


	UPDATE_LEN();
}

Value* StringValue::construct(FUNCS_ARGS args){

	if(args.size() == 0){
		value = "";
	} else {
		value = args.at(0)->as_string();
	}

	UPDATE_LEN();

	return this;
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
	// return "'" + as_string() + "'";
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

Value* StringValue::get(Value* key){
	if(key->type() == Types::T_NUMBER)
		return new StringValue(this->get_c(key->as_int()));
	else
		return this->get_prop(key);
}

void StringValue::set(Value* key, Value* value){
	if(key->type() == Types::T_NUMBER){
		this->value.replace(key->as_int(), 1, value->as_string());
	} else {
		this->set_prop(key, value);
	}
	UPDATE_LEN();
}

StringValue::~StringValue(){}