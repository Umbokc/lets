//
//  modules/type/type.hpp
//  lets
//
//  Created by Dragan Stepan on 07.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef modules__type__type_hpp
#define modules__type__type_hpp

#include <string>
#include <vector>
#include "../../include/main.h"
#include "../../include/l_function.h"
#include "../../include/l_array_value.hpp"

#include "../module.h"

class LetsModule__type{
public:

	static void run(ArrayValue*);

private:

	static bool is_done;

	static void set(lets_str_t);

	class F_To_i : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_To_s : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};
	class F_To_a : public ModuleParentClassFunctions{ public: Value* execute(FUNCS_ARGS);};

};


#endif /* modules__type__type_hpp */

