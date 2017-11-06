//
//  number.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/l_number.hpp"

Number::Number(){}

Number::Number(int& value){ add(value); }
Number::Number(double& value){ add(value); }
Number::Number(long& value){ add(value); }

Number& Number::operator=(const Number& n){ return *this; }

void Number::operator=(int value){ add(value); }
void Number::operator=(double value){ add(value); }
void Number::operator=(long value){ add(value);}

int Number::as_int(){
    return as_number<int>();
}

double Number::as_double(){
    return as_number<double>();
}

long Number::as_long(){
    return as_number<long>();
}

bool Number::is_int(){ return (type == NS_Number::TYPE_INT); }
bool Number::is_double(){ return (type == NS_Number::TYPE_DOUBLE); }
bool Number::is_long(){ return (type == NS_Number::TYPE_LONG); }

lets_str_t Number::as_string(){

    char buff[24];

    if(is_double()){
        sprintf(buff, "%.14g", this->val.d);
    } else if (is_long()){
        sprintf(buff, "%ld", this->val.l);
    } else {
        sprintf(buff, "%d", this->val.i);
    }

    lets_str_t s = buff;
    return s;
}

lets_str_t Number::to_s(){
    return as_string();
}

template<class T>
void Number::add(T value){
    if(typeid(value) == typeid(int)){
        this->val.i = (int)value;
        this->type = NS_Number::TYPE_INT;
    } else if(typeid(value) == typeid(double)){
        this->val.d = (double)value;
        this->type = NS_Number::TYPE_DOUBLE;
    } else if(typeid(value) == typeid(long)){
        this->val.l = (long)value;
        this->type = NS_Number::TYPE_LONG;
    } else {
        lets_error("Unknow Error")
    }
}

template<typename T>
T Number::as_number(){
    switch(type){
        case NS_Number::TYPE_INT:
            return static_cast<T>(this->val.i);
        case NS_Number::TYPE_LONG:
            return static_cast<T>(this->val.l);
        case NS_Number::TYPE_DOUBLE:
        default:
            return static_cast<T>(this->val.d);
    }
}

Number::~Number(){}
