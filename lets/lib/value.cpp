//
//  lets/lib/value.cpp
//  lets
//
//  Created by Dragan Stepan on 17.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include <iostream> // for dbg
#include "../../include/lib/value.hpp"
#include "../../include/lib/function.h"
#include "../../include/tools.hpp"
#include "../../include/exception/error.h"
#include "../../include/exception/execute.h"

size_t Value::get_count_vars(){
	return this->properties.size();
}

void Value::check_prop(const lets_str_t& key){
	if(!this->properties.is_exists(key)){
		throw ExecuteException(this->class_to_s() + ": Undefined attribute '" + key + "'");
	}
}

bool Value::prop_exists(const lets_str_t& key){
	return this->properties.is_exists(key);
}

void Value::check_prop_contant(const lets_str_t& key){
	if(this->properties.is_constant(key)){
		throw ExecuteException(this->class_to_s() + ": Cannot assign value to constant attribute '" + key + "'");
	}
}

Value* Value::get_prop(Value *key){
	return this->get_prop(key->as_string());
}

Value* Value::get_prop(const lets_str_t& key){
	this->check_prop(key);
	return this->properties.get(key);
}

void Value::set_prop(Value *key, Value *val){
	this->set_prop(key->as_string(), val);
}

void Value::set_prop(const lets_str_t& key, Value *val){
	this->set_prop(key, Property(val, false, false));
}

void Value::set_prop(const lets_str_t& key, Property var){
	this->check_prop_contant(key);
	this->properties.set(key, var);
}

void Value::define_prop(Value *key, Value *val){
	this->define_prop(key->as_string(), val);
}

void Value::define_prop(const lets_str_t& key, Value *val){
	this->define_prop(key, Property(val, false, false));
}

void Value::define_prop(const lets_str_t& key, Property var){
	this->properties.set(key, var);
}

void Value::set_class_name(const lets_str_t& name){
	this->class_name = name;
}

lets_str_t Value::get_class_name(){
	return this->class_name;
}

lets_str_t Value::class_to_s(){
	return "#<" + this->class_name + ": "+ NS_Tools::convert_to_string(this) +">";
}
