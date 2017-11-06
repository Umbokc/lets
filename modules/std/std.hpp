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
#include "../../include/l_function.h"
#include "../../include/l_array_value.hpp"

#include "../module.h"

class LetsModule__std{
public:
	static void run(ArrayValue*);

private:

	static bool is_done;

	static void set(lets_str_t);

	class F_Len : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Echo : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_Echos : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_NewArray : public ModuleParentClassFunctions{
		public: Value* execute(FUNCS_ARGS);
		private:ArrayValue* create_array(FUNCS_ARGS, int);
	};
	class F_IsExist : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};

};

#endif /* modules__std__std_hpp */

