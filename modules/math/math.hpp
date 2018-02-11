//
//  modules/math/math.hpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef modules__math__math_hpp
#define modules__math__math_hpp

#include <string>
#include <vector>
#include "../../include/main.h"
#include "../../include/lib/function.h"
#include "../../include/lib/array_value.hpp"

#include "../module.h"

class LetsModule__math{
public:

	static void run(ArrayValue*);

private:

	static bool is_done;

	static void set(lets_str_t);

	class F_Sin 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Cos 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Tan 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Acos 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Asin 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Atan 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Atan2 : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Cosh 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Sinh 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Tanh 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Acosh : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Asinh : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Atanh : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Sqrt 	: public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};

};

#endif /* modules__math__math_hpp */

