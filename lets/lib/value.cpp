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
#include "../../include/lib/null_value.hpp"
#include "../../include/tools.hpp"
#include "../../include/exception/error.h"
#include "../../include/exception/execute.h"


Variable::Variable(){}
Variable::Variable(Value* v):value(std::move(v)), is_private(false), is_constant(false){}
Variable::Variable(Value* v, bool is_p, bool is_c):value(std::move(v)), is_private(is_p), is_constant(is_c){}
lets_str_t Variable::to_s(){ return value->to_s(); }
Variable::~Variable(){}

VariablesContainer::VariablesContainer(){}
bool VariablesContainer::is_exists(const lets_str_t& name){
	return variables.find(name) != variables.end();
}
bool VariablesContainer::is_constant(const lets_str_t& name){
	if (this->is_exists(name))
		return variables.at(name).is_constant;
	else
		return false;
}
Value* VariablesContainer::get(const lets_str_t& name){
	if (this->is_exists(name))
		return variables.at(name).value;
	return NullValue::THE_NULL;
}
void VariablesContainer::set(const lets_str_t& name, Value* val){
	variables[name] = Variable(val);
}
void VariablesContainer::set(const lets_str_t& name, Variable var){
	variables[name] = var;
}
void VariablesContainer::remove(const lets_str_t& name){
	variables.erase(name);
}
size_t VariablesContainer:: size(){
	return variables.size();
}
lets_str_t VariablesContainer::to_s(){
	return "VariablesContainer";
}
VariablesContainer::~VariablesContainer(){}

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
	this->set_prop(key, Variable(val, false, false));
}

void Value::set_prop(const lets_str_t& key, Variable var){
	this->check_prop_contant(key);
	this->properties.set(key, var);
}

void Value::define_prop(Value *key, Value *val){
	this->define_prop(key->as_string(), val);
}

void Value::define_prop(const lets_str_t& key, Value *val){
	this->define_prop(key, Variable(val, false, false));
}

void Value::define_prop(const lets_str_t& key, Variable var){
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
