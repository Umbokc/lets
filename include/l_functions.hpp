//
//  l_functions.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef l_functions_hpp
#define l_functions_hpp

#include <string>
#include <map>
#include "main.h"

#include "l_function.h"
#include "l_function_container.h"


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


#endif /* l_functions_hpp */
