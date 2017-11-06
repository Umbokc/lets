//
//  modules/math/math.cpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <limits>

#include "math.hpp"
#include "../../include/l_number_value.hpp"
#include "../../include/l_string_value.hpp"
#include "../../include/l_functions.hpp"
#include "../../include/l_variables.h"
#include "../../include/ex_parse.h"

#define DEFENITION_CLASS_FUNC_MODULE_MATH(F_CLASS, M_FUNC, NUM_ARGS, TEXT_ERROR) \
	Value* LetsModule__math::F_##F_CLASS::execute(FUNCS_ARGS args){ \
		if(args.size() != NUM_ARGS) throw ParseException(TEXT_ERROR); \
		return new NumberValue(M_FUNC); \
	}

bool LetsModule__math::is_done = false;

void LetsModule__math::run(ArrayValue* elems){
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

void LetsModule__math::set(lets_str_t name){

	CHECK_AND_DEFINE_VAR_MODULE("PI", 				new NumberValue((double)M_PI))
	CHECK_AND_DEFINE_VAR_MODULE("E",					new NumberValue((double)M_E))
	CHECK_AND_DEFINE_VAR_MODULE("LOG2E",			new NumberValue((double)M_LOG2E))
	CHECK_AND_DEFINE_VAR_MODULE("LOG10E",			new NumberValue((double)M_LOG10E))
	CHECK_AND_DEFINE_VAR_MODULE("LN2",				new NumberValue((double)M_LN2))
	CHECK_AND_DEFINE_VAR_MODULE("LN10",				new NumberValue((double)M_LN10))
	CHECK_AND_DEFINE_VAR_MODULE("PI_2",				new NumberValue((double)M_PI_2))
	CHECK_AND_DEFINE_VAR_MODULE("PI_4",				new NumberValue((double)M_PI_4))
	CHECK_AND_DEFINE_VAR_MODULE("M_1_PI",			new NumberValue((double)M_1_PI))
	CHECK_AND_DEFINE_VAR_MODULE("M_2_PI",			new NumberValue((double)M_2_PI))
	CHECK_AND_DEFINE_VAR_MODULE("SQRTPI",			new NumberValue((double)sqrt(M_PI)))
	CHECK_AND_DEFINE_VAR_MODULE("M_2_SQRTPI", new NumberValue((double)M_2_SQRTPI))
	CHECK_AND_DEFINE_VAR_MODULE("SQRT2",			new NumberValue((double)M_SQRT2))
	CHECK_AND_DEFINE_VAR_MODULE("SQRT3",			new NumberValue((double)sqrt(3)))
	CHECK_AND_DEFINE_VAR_MODULE("SQRT1_2",		new NumberValue((double)M_SQRT1_2))
	CHECK_AND_DEFINE_VAR_MODULE("NAN",				new NumberValue((double)NAN))
	CHECK_AND_DEFINE_VAR_MODULE("I_MAX",			new NumberValue((int)std::numeric_limits<int>::max()))
	CHECK_AND_DEFINE_VAR_MODULE("L_MAX",			new NumberValue((long)std::numeric_limits<long>::max()))
	CHECK_AND_DEFINE_VAR_MODULE("INF",				new NumberValue((double)std::numeric_limits<double>::infinity()))

	CHECK_AND_DEFINE_FUNC_MODULE("sin", Sin)
	CHECK_AND_DEFINE_FUNC_MODULE("cos", Cos)
	CHECK_AND_DEFINE_FUNC_MODULE("tan", Tan)
	CHECK_AND_DEFINE_FUNC_MODULE("acos", Acos)
	CHECK_AND_DEFINE_FUNC_MODULE("asin", Asin)
	CHECK_AND_DEFINE_FUNC_MODULE("atan", Atan)
	CHECK_AND_DEFINE_FUNC_MODULE("atan2", Atan2)
	CHECK_AND_DEFINE_FUNC_MODULE("cosh", Cosh)
	CHECK_AND_DEFINE_FUNC_MODULE("sinh", Sinh)
	CHECK_AND_DEFINE_FUNC_MODULE("tanh", Tanh)
	CHECK_AND_DEFINE_FUNC_MODULE("acosh", Acosh)
	CHECK_AND_DEFINE_FUNC_MODULE("asinh", Asinh)
	CHECK_AND_DEFINE_FUNC_MODULE("atanh", Atanh)
	CHECK_AND_DEFINE_FUNC_MODULE("sqrt", Sqrt)

	if(name != "*")
		throw std::runtime_error("not found");
}

DEFENITION_CLASS_FUNC_MODULE_MATH(Sin, sin(args[0]->as_number()), 1, "Function sin(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Cos, cos(args[0]->as_number()), 1, "Function cos(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Tan, tan(args[0]->as_number()), 1, "Function tan(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Acos, acos(args[0]->as_number()), 1, "Function acos(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Asin, asin(args[0]->as_number()), 1, "Function asin(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Atan, atan(args[0]->as_number()), 1, "Function atan(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Atan2, atan2(args[0]->as_number(), args[1]->as_number()), 2, "Function atan2(arg*, arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Cosh, cosh(args[0]->as_number()), 1, "Function cosh(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Sinh, sinh(args[0]->as_number()), 1, "Function sinh(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Tanh, tanh(args[0]->as_number()), 1, "Function tanh(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Acosh, acosh(args[0]->as_number()), 1, "Function acosh(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Asinh, asinh(args[0]->as_number()), 1, "Function asinh(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Atanh, atanh(args[0]->as_number()), 1, "Function atanh(arg*) one args expected")
DEFENITION_CLASS_FUNC_MODULE_MATH(Sqrt, sqrt(args[0]->as_number()), 1, "Function sqrt(arg*) one args expected")
