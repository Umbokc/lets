#ifndef VARIABLES_H
#define VARIABLES_H

#define _USE_MATH_DEFINES
#include <stack>
#include <cmath>
#include <map>
#include "variable_container.h"

namespace NS_Variables{
	#define MAP_VAR std::map<std::string, VariableContainer*>

	static MAP_VAR variables = {
		{"false", new VariableContainer(ZERO, true)},
		{"true", new VariableContainer(ONE, true)},
	};

	static std::stack<MAP_VAR> thestack;

}

using namespace NS_Variables;

class Variables{
public:

	static void push(){
		thestack.push(MAP_VAR(variables));
	}

	static void pop(){
		thepop(&variables, thestack, thestack.size());
	}

	static bool is_exists(std::string key){
		return variables.find(key) != variables.end();
	}

	static bool is_constexpr(std::string key){
		return variables[key]->is_constant;
	}
	
	static Value* get(std::string key){
		if(!is_exists(key)) throw VariableDoesNotExistsException(key);
		return variables[key]->value;
	}

	static void set(std::string key, Value* value){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot assign value to constant \"" + key + "\"");
		variables[key] = new VariableContainer(value);
	}


	static void set_constexpr(std::string key, Value* value){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot assign value to constant \"" + key + "\"");
		variables[key] = new VariableContainer(value, true);
	}

	static void set_lets_varss(std::string key, Value* value, bool is_contstant){
		variables[key] = new VariableContainer(value, is_contstant);
	}

private:
	static void thepop(MAP_VAR *var, std::stack<MAP_VAR> the_stack, int size){

		int i = 0;
		MAP_VAR temp[size];
		while (!thestack.empty()){
			temp[i] = thestack.top();
			thestack.pop();
			++i;
		}

		for (int j = size - 1, l = 0; j >= 0; --j, ++l) {
			var[l] = temp[j];
		}

	}

};

#endif
