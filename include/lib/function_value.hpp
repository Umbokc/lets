//
//  include/lib/function_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__function_value_hpp
#define include__lib__function_value_hpp

#include "../main.h"
#include "function.h"

class FunctionValue : public Value{
    Function* value;
public:
    
    FunctionValue(Function*);
    
    bool as_bool();
    int as_int();
    double as_number();
    long as_long();
    Function* get_value();
    int len();
    lets_str_t as_string();
    lets_str_t to_s();
    Types type();

    bool equals(Value*);
    int compareTo(Value*);
    
    ~FunctionValue();
};

#endif /* include__lib__function_value_hpp */
