//
//  s_function_define_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_function_define_stat_hpp
#define s_function_define_stat_hpp

#include <string>
#include "main.h"
#include "arguments.hpp"
#include "statement.h"

class FunctionDefineStatement : virtual public Statement{
public:
    lets_str_t name;
    Arguments args;
    Statement *body;
    bool is_constexpr;
    
    FunctionDefineStatement(lets_str_t,Arguments,Statement *,bool);
    
    void execute();

    lets_str_t to_s();
    
    ~FunctionDefineStatement();
};

#endif /* s_function_define_stat_hpp */
