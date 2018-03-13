//
//  lets/lib/number.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include <typeinfo>
// #include <iomanip> // setprecision

#include "../../include/lib/number.hpp"

Number::Number(){}

Number::Number(int value){ add(value); }
Number::Number(double value){ add(value); }
Number::Number(long value){ add(value); }

int Number::as_int(){
	return as_number<int>();
}

double Number::as_double(){
	return as_number<double>();
}

long Number::as_long(){
	return as_number<long>();
}

bool Number::is_int(){ return (this->type == NS_Number::TYPE_INT); }
bool Number::is_double(){ return (this->type == NS_Number::TYPE_DOUBLE); }
bool Number::is_long(){ return (this->type == NS_Number::TYPE_LONG); }

lets_str_t Number::as_string(){

	if(this->is_double()){

		// std::ostringstream sstream;
		// sstream << std::setprecision(17) << this->val.d;
		// return sstream.str();

		char buff[24];
		sprintf(buff, "%.16g", this->val.d);
		lets_str_t r = buff;
		return r;

	} else {
		return to_str(this->is_long() ? (long)this->val.l : (int)this->val.i);
	}

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
