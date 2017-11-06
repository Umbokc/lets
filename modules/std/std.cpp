//
//  modules/std/std.cpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "std.hpp"
#include "../../include/l_string_value.hpp"
#include "../../include/l_number_value.hpp"
#include "../../include/l_functions.hpp"
#include "../../include/l_variables.h"
#include "../../include/ex_parse.h"
#include "../../include/tools.hpp"

bool LetsModule__std::is_done = false;

void LetsModule__std::run(ArrayValue* elems){
	if(!is_done){
		if (elems != NULL){
			for (int i = 0; i < elems->len(); ++i){
				try{
					set(elems->get(i)->to_s());
				} catch(std::exception& e) {
					throw ParseException("Unknown variable or function '" + elems->get(i)->to_s() + "' in module 'use'.");
				}
			}
		} else {
			is_done = true;
			set("*");
		}
	}
}


void LetsModule__std::set(lets_str_t name){

	CHECK_AND_DEFINE_VAR_MODULE("__dir__", new StringValue(NS_Tools::get_curr_dir()))

	CHECK_AND_DEFINE_FUNC_MODULE("len", Len)
	CHECK_AND_DEFINE_FUNC_MODULE("echo", Echo)
	CHECK_AND_DEFINE_FUNC_MODULE("echos", Echos)
	CHECK_AND_DEFINE_FUNC_MODULE("newArray", NewArray)
	CHECK_AND_DEFINE_FUNC_MODULE("is_exist", IsExist)

	if(name != "*")
		throw std::runtime_error("not found");
}

Value* LetsModule__std::F_Len::execute(FUNCS_ARGS args){
	if(args.size() != 1) throw ParseException("Function len(arg*) one args expected");
	return new NumberValue(args[0]->len());
}

Value* LetsModule__std::F_Echo::execute(FUNCS_ARGS args){
	for(auto a : args){
		std::cout.precision(a->to_s().length());
		std::cout << std::fixed << a->to_s() << " ";
	}
	std::cout << std::endl;
	return NumberValue::ZERO;
}

Value* LetsModule__std::F_Echos::execute(FUNCS_ARGS args){
	for(auto a : args){
		std::cout.precision(a->to_s().length());
		std::cout << std::fixed << a->to_s() << std::endl;
	}
	return NumberValue::ZERO;
}

Value* LetsModule__std::F_NewArray::execute(FUNCS_ARGS args){
	return create_array(args, 0);
}
ArrayValue* LetsModule__std::F_NewArray::create_array(FUNCS_ARGS args, int index){

	int size = args[index]->as_int();
	int last = (int)args.size() -1;

	ArrayValue *array = new ArrayValue(size);

	if(index == last){
		for (int i = 0; i < size; ++i){
			array->set(i, NumberValue::ZERO);
		}
	} else if(index < last) {
		for (int i = 0; i < size; ++i){
			array->set(i, create_array(args, index+1));
		}
	}

	return array;
}


Value* LetsModule__std::F_IsExist::execute(FUNCS_ARGS args){
	for(auto a : args){
		lets_str_t name = a->to_s();
		if(!Variables::is_exists_all(name) && !Functions::is_exists(name)){
			return NumberValue::ZERO;
		}
	}
	return NumberValue::ONE;
}