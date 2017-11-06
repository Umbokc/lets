//
//  l_value.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lib__value_h
#define lib__value_h

#include "l_types.h"

class Value {
public:
    
    virtual int as_int() = 0;
    virtual double as_number() = 0;
    virtual long as_long() = 0;
    virtual lets_str_t as_string() = 0;
    virtual lets_str_t to_s() = 0;
    virtual int len() = 0;
    virtual Types type() = 0;
    virtual bool equals(Value*) = 0;
    virtual int compareTo(Value *obj) = 0;
    
    //virtual ~Value();
};

#endif /* lib__value_h */
