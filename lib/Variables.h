#ifndef VARIABLES_H
#define VARIABLES_H

#define _USE_MATH_DEFINES
#include <stack>
#include <cmath>
#include <map>
#include "variable_container.h"


namespace NS_Variables{

	#define VARIABLE_MAP std::map<std::string, VariableContainer*>

	static VARIABLE_MAP variables = {};

	static VARIABLE_MAP global_variables = {
		{"false", new VariableContainer(ZERO, true)},
		{"true", new VariableContainer(ONE, true)},
	};

	static std::stack<VARIABLE_MAP> the_stack;

}

using namespace NS_Variables;

class Variables{
public:

	static void push(){
		the_stack.push(VARIABLE_MAP(variables));
	}

	static void pop(){
		variables = the_stack.top();
		the_stack.pop();
		// thepop(&variables, the_stack, the_stack.size());
	}

	static bool is_exists_all(std::string key){
		return is_exists_g(key) || is_exists(key);
	}
	
	static bool is_exists(std::string key){
		return variables.find(key) != variables.end();
	}

	static bool is_exists_g(std::string key){
		return global_variables.find(key) != global_variables.end();
	}

	static bool is_constexpr(std::string key){
		return (is_exists(key)) ? variables[key]->is_constant :
					 (is_exists_g(key)) ? global_variables[key]->is_constant : 
					 false;
	}
	
	static Value* get(std::string key){
		if(!is_exists_all(key)) throw VariableDoesNotExistsException(key);

		if(is_exists_g(key)){
			return global_variables[key]->value;
		}

		return variables[key]->value;
	}

	static void set(std::string key, Value* value){
		set_var(key, value, false, is_global_var(key), true);
	}

	static void set_constexpr(std::string key, Value* value){
		set_var(key, value, true, is_global_var(key), true);
	}

	static void set_lets_vars(std::string key, Value* value, bool is_contstant){
		set_var(key, value, is_contstant, is_global_var(key), false);
	}

	static void set_var(std::string key, Value* value, bool is_const, bool is_glob, bool check_const){
		if(is_constexpr(key) && check_const) throw ParseException("Cannot assign value to constant \"" + key + "\"");
		if(is_glob){
			global_variables[key] = new VariableContainer(value, is_const);
		} else {
			variables[key] = new VariableContainer(value, is_const);
		}
	}

	static void show(){
		std::string result = "Variables: \n";
			int i = 0;
			int size = variables.size();
			for (auto& elem : variables){
				result += "\t";
				result += elem.first;
				result +=  " : ";
				result += elem.second->value->to_s();
				if(i != size-1) result +=  ", \n";
				i++;
			}
			i = 0;
			size = global_variables.size();
			if(size > 0) result +=  ", \n";
			for (auto& elem : global_variables){
				result += "\t";
				result += elem.first;
				result +=  " : ";
				result += elem.second->value->to_s();
				if(i != size-1) result +=  ", \n";
				i++;
			}
			result +=  "\nend";

			std::cout << result << std::endl;
	}

private:
	static bool is_global_var(std::string key){
		if(is_exists_g(key) || key[0] == '$'){
			return true;
		} else {
			return false;
		}
	}

	static void thepop(VARIABLE_MAP *var, std::stack<VARIABLE_MAP> the_stack, int size){

		int i = 0;
		VARIABLE_MAP temp[size];
		while (!the_stack.empty()){
			temp[i] = the_stack.top();
			the_stack.pop();
			++i;
		}

		for (int j = size - 1, l = 0; j >= 0; --j, ++l) {
			var[l] = temp[j];
		}
	}

};

#endif
