//
//  include/lib/functions.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__functions_hpp
#define include__lib__functions_hpp

#include <string>
#include <map>
#include "../main.h"

#include "function.h"
#include "function_container.h"


class Functions{
public:
	static lets_map_t<lets_str_t, FunctionContainer*> functions;

	static bool is_exists(lets_str_t);
	static bool is_constexpr(lets_str_t);
	static Function* get(lets_str_t);
	static void set(lets_str_t, Function*);
	static void set_constexpr(lets_str_t, Function*);
	static void set_lets_funcs(lets_str_t, Function*, bool);

//    static void show();
};


#endif /* include__lib__functions_hpp */
