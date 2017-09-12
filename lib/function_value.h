#ifndef FUNCTION_VALUE_H
#define FUNCTION_VALUE_H

#include "function.h"

class FunctionValue : public Value{
	Function* value;
public:

	FunctionValue(Function* value):value(std::move(value)){}

	int as_int(){
		return (int)as_number();
	}

	double as_number(){
		throw ParseException("Cannot cast function to number");
	}

	long as_long(){
		return (long)as_number();
	}
	
	Function* get_value(){
		return value;
	}
	
	std::string as_string(){
		return "function";
	}
	
	std::string to_s(){
		return as_string();
	}
	
	Types type(){
		return Types::T_FUNCTION;
	}

	~FunctionValue();
};

#endif
