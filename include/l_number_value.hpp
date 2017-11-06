//
//  l_number_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lib__number_value_hpp
#define lib__number_value_hpp

#include "l_value.h"
#include "l_number.hpp"

class NumberValue : public Value{
private:
public:
    Number value;
    static NumberValue* ZERO;
    static NumberValue* ONE;
    static NumberValue* NEGATE_ONE;
    
    NumberValue(int);
    NumberValue(double);
    NumberValue(long);
    
    bool as_bool();
    int as_int();
    double as_number();
    long as_long();
    
    int len();
    Types type();
    
    lets_str_t as_string();
    lets_str_t to_s();
    
    bool equals(Value*);
    int compareTo(Value*);
    
    ~NumberValue();
};

#endif /* lib__number_value_hpp */
