//
//  modules/std/std.cpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <random>
#include "std.hpp"
#include "../../include/lib/include_values.h"
#include "../../include/lib/functions.hpp"
#include "../../include/lib/variables.hpp"
#include "../../include/exception/parse.h"
#include "../../include/tools.hpp"

#define DEFENITION_CLASS_FUNC_MODULE_STD(F_CLASS, EXECUTE, TO_S) \
	Value* LetsModule__std::F_##F_CLASS::execute(FUNCS_ARGS args) EXECUTE \
	lets_str_t LetsModule__std::F_##F_CLASS::to_s() TO_S

bool LetsModule__std::is_done = false;

void LetsModule__std::run(ArrayValue* elems){
	if(!is_done){
		if (elems != NULL){
			for (int i = 0; i < elems->len(); ++i){
				try{
					set(elems->get(i)->to_s());
				} catch(std::exception& e) {
					throw ParseException("Unknown variable or function '" + elems->get(i)->to_s() + "' in module 'std'.");
				}
			}
		} else {
			is_done = true;
			set("*");
		}
	}
}


void LetsModule__std::set(lets_str_t name){

	CHECK_AND_DEFINE_FUNC_MODULE("len", Len)
	CHECK_AND_DEFINE_FUNC_MODULE("echo", Echo)
	CHECK_AND_DEFINE_FUNC_MODULE("echos", Echos)
	CHECK_AND_DEFINE_FUNC_MODULE("is_exist", IsExist)
	CHECK_AND_DEFINE_FUNC_MODULE("rand", Rand)

	if(name != "*")
		throw std::runtime_error("not found");
}

DEFENITION_CLASS_FUNC_MODULE_STD(Len, {
	if(args.size() != 1) throw ParseException("Function len(arg*) one args expected");
	return new NumberValue(args[0]->len());
}, {
	return "len";
})

DEFENITION_CLASS_FUNC_MODULE_STD(Echo, {
	for(auto a : args){
		std::cout.precision(a->to_s().length());
		std::cout << std::fixed << a->to_s() << " ";
	}
	std::cout << std::endl;
	return NullValue::THE_NULL;
}, {
	return "echo";
})

DEFENITION_CLASS_FUNC_MODULE_STD(Echos, {
	for(auto a : args){
		std::cout.precision(a->to_s().length());
		std::cout << std::fixed << a->to_s() << " ";
	}
	std::cout << std::endl;
	return NullValue::THE_NULL;
}, {
	return "echos";
})

DEFENITION_CLASS_FUNC_MODULE_STD(IsExist, {
	for(auto a : args){
		lets_str_t name = a->to_s();
		if(!Variables::is_exists_all(name) && !Functions::is_exists(name)){
			return BoolValue::FALSE;
		}
	}
	return BoolValue::TRUE;
}, {
	return "is_exist";
})

DEFENITION_CLASS_FUNC_MODULE_STD(Rand, {
	// std::srand(unsigned(std::time(0)));
	int min = 0;
	int max = RAND_MAX;

	if(args.size() == 2){
		min = args.at(0)->as_int();
		max = args.at(1)->as_int() - 1;
	} else if(args.size() == 1){
		max = args.at(0)->as_int() - 1;
	}

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

	return new NumberValue(uni(rng));
}, {
	return "rand";
})
