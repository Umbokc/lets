//
//  variables.cpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/l_variables.h"
#include "../include/ex_execute.h"
#include "../include/l_bool_value.hpp"
#include "../include/l_number_value.hpp"

#define Lets__FIRST_CHAR_GLOB_VAR '@'
#define Lets__FIRST_CHAR_CONST_VAR '_'
#define Lets__FIRST_CHARS_CONST_GLOB_VAR "__"

Variables::Scope *Variables::scope = new Variables::Scope();
Variables::VARIABLE_MAP Variables::global_variables = {
	{"false", new VariableContainer(BoolValue::FALSE, true)},
	{"true", new VariableContainer(BoolValue::TRUE, true)},
};

void Variables::push() {
	Scope *newScope = new Scope(scope);
	scope = newScope;
}

void Variables::pop() {
	if (scope->parent != NULL) {
		scope = scope->parent;
	}
}

bool Variables::is_exists(lets_str_t key){
	return scope->variables.find(key) != scope->variables.end();
}

bool Variables::is_exists_global(lets_str_t key){
	return global_variables.find(key) != global_variables.end();
}

bool Variables::is_exists_all(lets_str_t key){
	return is_exists_global(key) || is_exists(key);
}

bool Variables::is_constexpr(lets_str_t key){
	return (is_exists(key)) ? scope->variables.at(key)->is_constant :
				(is_exists_global(key)) ? global_variables.at(key)->is_constant : 
				false;
}

bool Variables::is_global_to_set(lets_str_t key){
	return (key[0] == Lets__FIRST_CHAR_GLOB_VAR);
}

bool Variables::is_const_to_set(lets_str_t key){
	return (key[0] == Lets__FIRST_CHAR_CONST_VAR);
}

bool Variables::is_global_const_to_set(lets_str_t key){
	return (key[0] == Lets__FIRST_CHARS_CONST_GLOB_VAR[0] && key[1] == Lets__FIRST_CHARS_CONST_GLOB_VAR[1]);
}

Value* Variables::get(lets_str_t key){

	if (is_exists(key))
		return scope->variables.at(key)->value;
	else if(is_exists_global(key))
		return global_variables.at(key)->value;

	return NumberValue::ZERO;
}

void Variables::set(lets_str_t key, Value* value){
	if(is_constexpr(key)) throw ExecuteException("Cannot assign value to constant \"" + key + "\"");

	// $var or __var
	if(is_global_to_set(key) || is_global_const_to_set(key)){
		global_variables[key] = new VariableContainer(value, is_global_const_to_set(key));
	} else {
		scope->variables[key] = new VariableContainer(value, is_const_to_set(key));
	}

}

void Variables::define(lets_str_t key, Value* value){
	scope->variables[key] = new VariableContainer(value);
}

void Variables::define_lets(lets_str_t key, Value* value, bool is_const){
	global_variables[key] = new VariableContainer(value, is_const);
}

void Variables::remove(lets_str_t key){
	scope->variables.erase(key);
}

void Variables::show(){
	lets_str_t result = "Variables : \n";
	int i = 0;
	// ScopeVar *the_scope = (the == "parent") ? scope->parent : scope;
	uint size = (uint)scope->variables.size();
	result += "scope\n";
	for (auto& elem : scope->variables){
		result += "\t" + elem.first + " : " + elem.second->to_s();
		if(i != size-1) result +=  ", \n";
		i++;
	}
	result +=  "\nend";
	
	lets_output(result)
}
