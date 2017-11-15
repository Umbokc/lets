//
//  l_array_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lib_array_value_hpp
#define lib_array_value_hpp

#include <vector>
#include <string>
#include "main.h"
#include "l_value.h"

class ArrayValue : public Value{
    lets_vector_t<Value *> elements;
public:
    
    ArrayValue(int);
    ArrayValue(Value*);
    ArrayValue(lets_vector_t<Value *> );
    ArrayValue(ArrayValue *);
    
    void add(Value *);
    void add_forward(Value *);
    
    Value *get(int);
    Value *get_always(int);
    lets_vector_t<Value *> get_all();

    bool has(Value*);

    void set(int , Value *);
    
    int as_int();
    double as_number();
    long as_long();
    int len();
    int size();
    
    lets_str_t as_string();
    lets_str_t to_s();
    Types type();
    
    bool equals(Value* );
    int compareTo(Value *);
    
    ~ArrayValue();
};

namespace NS_ArrayValue{
    ArrayValue *add(ArrayValue *arr, Value *value);
    ArrayValue *add_forward(ArrayValue *arr, Value *value);
    ArrayValue *merge(ArrayValue *value1, ArrayValue *value2);
};

#endif /* lib_array_value_hpp */
