//
//  arguments.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__arguments_hpp
#define ast__arguments_hpp

#include <string>
#include <vector>
#include "main.h"
#include "argument.hpp"

class Arguments {
private:
    int required;
    lets_vector_t<Argument> arguments;
public:
    
    Arguments();
    
    void add_required(lets_str_t name);
    void add_optional(lets_str_t name, Expression* expr);
    
    Argument get(int i);
    
    int get_required();
    int get_size();
    
    lets_str_t to_s();
    
    ~Arguments();
};

#endif /* ast__arguments_hpp */
