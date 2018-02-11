//
//  lets/lib/function_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/lib/function_value.hpp"
#include "../../include/exception/execute.h"

FunctionValue::FunctionValue(Function* value):value(std::move(value)){}

bool FunctionValue::as_bool(){
    return (bool)as_number();
}

int FunctionValue::as_int(){
    return (int)as_number();
}

double FunctionValue::as_number(){
    throw ExecuteException("Cannot cast function to number");
}

long FunctionValue::as_long(){
    return (long)as_number();
}

Function* FunctionValue::get_value(){
    return value;
}

int FunctionValue::len(){
    return -1;
}

lets_str_t FunctionValue::as_string(){
    return this->value->to_s();
}

lets_str_t FunctionValue::to_s(){
    return as_string();
}

Types FunctionValue::type(){
    return Types::T_FUNCTION;
}

bool FunctionValue::equals(Value* obj) {
    if (this == obj) return true;
    if (obj == NULL) return false;
    if(dynamic_cast<FunctionValue*>(obj))
        return this->value == dynamic_cast<FunctionValue*>(obj)->value;
    
    return false;
}

int FunctionValue::compareTo(Value *obj){
    if (obj->type() == this->type()) {
        int length_compare = lets_compare(len(), dynamic_cast<FunctionValue*>(obj)->len());
        if (length_compare != 0) return length_compare;
    }
    return lets_compare(as_string(), obj->as_string());
}

FunctionValue::~FunctionValue(){
    
}
