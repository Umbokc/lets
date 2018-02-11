//
//  include/lib/variables.hpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__variables_hpp
#define include__lib__variables_hpp

#include <string>
#include <map>
#include "../main.h"
#include "value.h"

class Variables {
public:

	class VariableContainer {
	public:
		Value *value;
		bool is_constant;

		VariableContainer(){}

		VariableContainer(Value *v):value(std::move(v)), is_constant(false){}
		VariableContainer(Value *v, bool is_c):value(std::move(v)), is_constant(std::move(is_c)){}

		lets_str_t to_s(){
			return value->to_s();
		}

		~VariableContainer(){}
	};

	typedef lets_map_t<lets_str_t, VariableContainer*> VARIABLE_MAP;

	class Scope {
	public:
		Scope *parent;
		VARIABLE_MAP variables;
		Scope():parent(NULL) {}
		Scope(Scope *parent):parent(parent){}
		// Scope(Scope *parent):parent(std::move(parent)){}
	};

	static Scope *scope;
	static VARIABLE_MAP global_variables;

	static void push();
	static void pop();

	static VARIABLE_MAP variables();

	static bool is_exists(lets_str_t);
	static bool is_exists_global(lets_str_t);
	static bool is_exists_all(lets_str_t);
	static bool is_constexpr(lets_str_t);

	static bool is_global_to_set(lets_str_t);
	static bool is_const_to_set(lets_str_t);
	static bool is_global_const_to_set(lets_str_t);

	static Value* get(lets_str_t);

	static void set(lets_str_t, Value*);
	static void define(lets_str_t, Value*);
	static void define_lets(lets_str_t, Value*, bool);

	static void remove(lets_str_t);

	static void show();
};

#endif /* include__lib__variables_hpp */
