//
//  l_user_define_function.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lib__user_define_function_hpp
#define lib__user_define_function_hpp

#include <string>
#include "main.h"
#include "l_function.h"
#include "argument.hpp"
#include "arguments.hpp"
#include "statement.h"

class UserDefineFunction : public Function {
public:
    Arguments args;
    Statement *body;
    
    UserDefineFunction(Arguments, Statement *);
    
    int get_args_count();
    
    Value* execute(FUNCS_ARGS);
    lets_str_t get_arg_name(int i);
    
    lets_str_t to_s();
};

#endif /* lib__user_define_function_hpp */
