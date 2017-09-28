#ifndef LETS_MODULE_MATH_H
#define LETS_MODULE_MATH_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include "math_functions.h"

namespace Lets_Module_Math {

	void run() {
		Variables::set_lets_varss("PI", new NumberValue(M_PI), true);
		Variables::set_lets_varss("E", new NumberValue(M_E), true);
		Variables::set_lets_varss("LOG2E", new NumberValue(M_LOG2E), true);
		Variables::set_lets_varss("LOG10E", new NumberValue(M_LOG10E), true);
		Variables::set_lets_varss("LN2", new NumberValue(M_LN2), true);
		Variables::set_lets_varss("LN10", new NumberValue(M_LN10), true);
		Variables::set_lets_varss("PI_2", new NumberValue(M_PI_2), true);
		Variables::set_lets_varss("PI_4", new NumberValue(M_PI_4), true);
		Variables::set_lets_varss("M_1_PI", new NumberValue(M_1_PI), true);
		Variables::set_lets_varss("M_2_PI", new NumberValue(M_2_PI), true);
		Variables::set_lets_varss("SQRTPI", new NumberValue(sqrt(M_PI)), true);
		Variables::set_lets_varss("M_2_SQRTPI", new NumberValue(M_2_SQRTPI), true);
		Variables::set_lets_varss("SQRT2", new NumberValue(M_SQRT2), true);
		Variables::set_lets_varss("SQRT3", new NumberValue(sqrt(3)), true);
		Variables::set_lets_varss("SQRT1_2", new NumberValue(M_SQRT1_2), true);
		Variables::set_lets_varss("NAN", new NumberValue(NAN), true);
		Variables::set_lets_varss("I_MAX", new NumberValue(std::numeric_limits<int>::max()), true);
		Variables::set_lets_varss("MAX", new NumberValue(std::numeric_limits<double>::max()), true);
		Variables::set_lets_varss("INF", new NumberValue(std::numeric_limits<double>::infinity()), true);

		Functions::set_lets_funcs("sin", new Lets_Modules_Math::LMM_Sin(), true);
		Functions::set_lets_funcs("cos", new Lets_Modules_Math::LMM_Cos(), true);
		Functions::set_lets_funcs("tan", new Lets_Modules_Math::LMM_Tan(), true);
		Functions::set_lets_funcs("acos", new Lets_Modules_Math::LMM_Acos(), true);
		Functions::set_lets_funcs("asin", new Lets_Modules_Math::LMM_Asin(), true);
		Functions::set_lets_funcs("atan", new Lets_Modules_Math::LMM_Atan(), true);
		Functions::set_lets_funcs("atan2", new Lets_Modules_Math::LMM_Atan2(), true);
		Functions::set_lets_funcs("cosh", new Lets_Modules_Math::LMM_Cosh(), true);
		Functions::set_lets_funcs("sinh", new Lets_Modules_Math::LMM_Sinh(), true);
		Functions::set_lets_funcs("tanh", new Lets_Modules_Math::LMM_Tanh(), true);
		Functions::set_lets_funcs("acosh", new Lets_Modules_Math::LMM_Acosh(), true);
		Functions::set_lets_funcs("asinh", new Lets_Modules_Math::LMM_Asinh(), true);
		Functions::set_lets_funcs("atanh", new Lets_Modules_Math::LMM_Atanh(), true);
		Functions::set_lets_funcs("sqrt", new Lets_Modules_Math::LMM_Sqrt(), true);
	}

}

#endif