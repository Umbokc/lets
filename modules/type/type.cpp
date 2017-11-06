//
//  modules/type/type.cpp
//  lets
//
//  Created by Dragan Stepan on 07.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "type.hpp"

#include <iostream>

#include "../../include/l_number_value.hpp"
#include "../../include/l_array_value.hpp"
#include "../../include/l_string_value.hpp"
#include "../../include/l_functions.hpp"
// #include "../../include/l_variables.h"
#include "../../include/ex_parse.h"

#define DEFENITION_CLASS_FUNC_MODULE_MATH(F_CLASS, M_FUNC, NUM_ARGS, TEXT_ERROR) \
	Value* LetsModule__type::F_##F_CLASS::execute(FUNCS_ARGS args){ \
		if(args.size() != NUM_ARGS) throw ParseException(TEXT_ERROR); \
		return M_FUNC; \
	}

bool LetsModule__type::is_done = false;

void LetsModule__type::run(ArrayValue* elems){
	if(!is_done){
		if (elems != NULL){
			for (int i = 0; i < elems->len(); ++i){
				try{
					set(elems->get(i)->to_s());
				} catch(std::exception& e) {
					throw ParseException("Unknown variable or function '" + elems->get(i)->to_s() + "' in module 'math'.");
				}
			}
		} else {
			is_done = true;
			set("*");
		}
	}
}

void LetsModule__type::set(lets_str_t name){

	CHECK_AND_DEFINE_FUNC_MODULE("to_i", To_i)
	CHECK_AND_DEFINE_FUNC_MODULE("to_s", To_s)
	CHECK_AND_DEFINE_FUNC_MODULE("to_a", To_a)

	if(name != "*")
		throw std::runtime_error("not found");
}

DEFENITION_CLASS_FUNC_MODULE_MATH(To_i, new NumberValue(args[0]->as_int()), 1, "Function to_i(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(To_s, new StringValue(args[0]->as_string()), 1, "Function to_s(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(To_a, new ArrayValue(args[0]), 1, "Function to_s(arg*) one args expected")
