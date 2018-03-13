//
//  modules/std/std.hpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef modules__std__std_hpp
#define modules__std__std_hpp

#include <string>
#include <vector>
#include "../../include/main.h"
#include "../../include/lib/function.h"
#include "../../include/lib/array_value.hpp"

#include "../module.h"

class LetsModule__std{
public:
	static void run(ArrayValue*);

private:

	static bool is_done;

	static void set(lets_str_t);

	class F_Len : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS); lets_str_t to_s();};
	class F_Echo : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS); lets_str_t to_s();};
	class F_Echos : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS); lets_str_t to_s();};
	class F_IsExist : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS); lets_str_t to_s();};
	class F_Rand : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS); lets_str_t to_s();};

};

#endif /* modules__std__std_hpp */

