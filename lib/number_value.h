#ifndef NUMBER_VALUE_H
#define NUMBER_VALUE_H
#include <string>

class NumberValue : virtual public Value{
private:
	Number value;
public:

	NumberValue(int value){
		this->value = value;
	}

	NumberValue(double value){
		this->value = value;
	}

	NumberValue(long value){
		this->value = value;
	}

	int as_int(){
		return value.as_int();
	}

	double as_number(){
		return value.as_double();
	}

	long as_long(){
		return value.as_long();
	}
	
	std::string as_string(){
		return value.as_string();
	}
	
	std::string to_s(){
		return as_string();
	}

	Types type(){
		return Types::T_NUMBER;
	}

	~NumberValue(){
		
	}
	
};
static NumberValue* ZERO = new NumberValue(0);
static NumberValue* ONE = new NumberValue(1);
static NumberValue* NEGATE_ONE = new NumberValue(-1);

#endif