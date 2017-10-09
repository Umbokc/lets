#ifndef VARIABLES_H
#define VARIABLES_H

#define _USE_MATH_DEFINES
#include <stack>
#include <cmath>
#include <map>
#include "variable_container.h"

namespace Variables{

	#define VARIABLE_MAP std::map<std::string, VariableContainer*>
	
	static VARIABLE_MAP variables = {};
	static VARIABLE_MAP global_variables = {
		{"false", new VariableContainer(ZERO, true)},
		{"true", new VariableContainer(ONE, true)},
	};

	static std::stack<VARIABLE_MAP> the_stack;

	static void push();
	static void pop();
	static bool is_exists_var(std::string key);
	static bool is_exists_global(std::string key);
	static bool is_constexpr(std::string key);
	static bool is_const_to_set(std::string key);
	static bool is_exists_all(std::string key);
	static Value* get(std::string key);
	static void set(std::string key, Value* value);
	static void set_lets_vars(std::string key, Value* value, bool is_contstant);
	// static void show();
	static bool check_the_global(std::string key);
	static bool check_the_const(std::string key);
	static bool check_the_global_const(std::string key);
	// static void thepop(VARIABLE_MAP *var, std::stack<VARIABLE_MAP> the_stack, int size);


	static void push(){
		the_stack.push(VARIABLE_MAP(variables));
	}

	static void pop(){
		variables = the_stack.top();
		the_stack.pop();
		// thepop(&variables, the_stack, the_stack.size());
	}
	
	static bool is_exists_var(std::string key){
		return variables.find(key) != variables.end();
	}

	static bool is_exists_global(std::string key){
		return global_variables.find(key) != global_variables.end();
	}

	static bool is_constexpr(std::string key){
		return (is_exists_var(key)) ? variables[key]->is_constant :
					 (is_exists_global(key)) ? global_variables[key]->is_constant : 
					 false;
	}

	static bool is_const_to_set(std::string key){
		return check_the_const(key) || check_the_global_const(key);
	}

	static bool is_exists_all(std::string key){
		return is_exists_global(key) || is_exists_var(key);
	}
	
	static Value* get(std::string key){
		if(!is_exists_all(key)) throw VariableDoesNotExistsException(key);
		return is_exists_global(key) ? global_variables[key]->value : variables[key]->value;
	}

	static void set(std::string key, Value* value){
		if(is_constexpr(key)) throw ParseException("Cannot assign value to constant \"" + key + "\"");
		bool is_const = is_const_to_set(key);
		if(check_the_global(key) || check_the_global_const(key)){
			global_variables[key] = new VariableContainer(value, is_const);
		} else {
			variables[key] = new VariableContainer(value, is_const);
		}
	}

	static void set_lets_vars(std::string key, Value* value, bool is_contstant){
		global_variables[key] = new VariableContainer(value, is_contstant);
	}
	
	// static void show(){
	// 	std::string result = "Variables: \n";
	// 		int i = 0;
	// 		int size = variables.size();
	// 		for (auto& elem : variables){
	// 			result += "\t";
	// 			result += elem.first;
	// 			result +=  " : ";
	// 			result += elem.second->value->to_s();
	// 			if(i != size-1) result +=  ", \n";
	// 			i++;
	// 		}
	// 		i = 0;
	// 		size = global_variables.size();
	// 		if(size > 0) result +=  ", \n";
	// 		for (auto& elem : global_variables){
	// 			result += "\t";
	// 			result += elem.first;
	// 			result +=  " : ";
	// 			result += elem.second->value->to_s();
	// 			if(i != size-1) result +=  ", \n";
	// 			i++;
	// 		}
	// 		result +=  "\nend";

	// 		std::cout << result << std::endl;
	// }

	static bool check_the_global(std::string key){
		if(is_exists_global(key) || key[0] == '$'){
			return true;
		} else {
			return false;
		}
	}

	static bool check_the_const(std::string key){
		if(key[0] == '_'){
			return true;
		} else {
			return false;
		}
	}

	static bool check_the_global_const(std::string key){
		if(key[0] == '_' && key[1] == '_'){
			return true;
		} else {
			return false;
		}
	}

	// static void thepop(VARIABLE_MAP *var, std::stack<VARIABLE_MAP> the_stack, int size){

	// 	int i = 0;
	// 	VARIABLE_MAP temp[size];
	// 	while (!the_stack.empty()){
	// 		temp[i] = the_stack.top();
	// 		the_stack.pop();
	// 		++i;
	// 	}

	// 	for (int j = size - 1, l = 0; j >= 0; --j, ++l) {
	// 		var[l] = temp[j];
	// 	}
	// }

};

#endif
