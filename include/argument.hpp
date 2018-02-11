//
//  include/argument.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__argument_hpp
#define include__argument_hpp

#include <string>
#include "main.h"
#include "declaration.h"
#include "expression.h"

class Argument {
private:
    lets_str_t name;
    Expression *value_expr;
public:
    Argument();
    Argument(lets_str_t);
    Argument(lets_str_t, Expression*);
    
    lets_str_t get_name();
    Expression *get_value_expr();
    
    lets_str_t to_s();
    
    ~Argument();
    
};

#endif /* include__argument_hpp */
