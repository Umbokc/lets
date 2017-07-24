#ifndef VARIABLES_H
#define VARIABLES_H

#define _USE_MATH_DEFINES
#include <stack>
#include <cmath>
#include <map>
#include "variable_container.h"

using namespace std;

namespace Variables_vars{
	static map<string, VariableContainer*> variables = {
		{"false", new VariableContainer(ZERO, true)},
		{"true", new VariableContainer(ONE, true)},
	};

	static stack<map<string, VariableContainer*>> thestack;

}

using namespace Variables_vars;

class Variables{
public:

	static void push(){
		thestack.push(map<string, VariableContainer*>(variables));
	}

	static void pop(){
		thepop(&variables, thestack, thestack.size());
	}

	static bool is_exists(string key){
		return variables.find(key) != variables.end();
	}

	static bool is_constexpr(std::string key){
		return variables[key]->is_constant;
	}
	
	static Value* get(string key){
		if(!is_exists(key)) return ZERO;
		return variables[key]->value;
	}

	static void set(string key, Value* value){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot assign value to constant \"" + key + "\"");
		variables[key] = new VariableContainer(value);
	}


	static void set_constexpr(string key, Value* value){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot assign value to constant \"" + key + "\"");
		variables[key] = new VariableContainer(value, true);
	}

	static void set_lets_varss(string key, Value* value, bool is_contstant){
		variables[key] = new VariableContainer(value, is_contstant);
	}

private:
	static void thepop(map<string, VariableContainer*> *var, stack<map<string, VariableContainer*>> the_stack, int size){

		int i = 0;
		map<string, VariableContainer*> temp[size];
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
