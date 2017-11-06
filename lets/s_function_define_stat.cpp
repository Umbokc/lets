//
//  s_function_define_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_function_define_stat.hpp"
#include "../include/l_user_define_function.hpp"
#include "../include/l_functions.hpp"

FunctionDefineStatement::FunctionDefineStatement(lets_str_t name, Arguments args, Statement *body, bool is_constexpr):
name(std::move(name)), args(std::move(args)), body(std::move(body)), is_constexpr(std::move(is_constexpr))
{}

void FunctionDefineStatement::execute(){
    if(is_constexpr)
        Functions::set_constexpr(name, new UserDefineFunction(args, body));
    else
        Functions::set(name, new UserDefineFunction(args, body));
}

lets_str_t FunctionDefineStatement::to_s(){
    lets_str_t result = "def " + name;
    result +=  " ( " + args.to_s() + " ) ";
    result += body->to_s();
    return result;
}

FunctionDefineStatement::~FunctionDefineStatement(){
    // delete[] body;
}



