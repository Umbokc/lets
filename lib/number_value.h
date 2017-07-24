#ifndef NUMBER_VALUE_H
#define NUMBER_VALUE_H
#include <string>

class NumberValue : virtual public Value{
private:
	double value;
public:

	NumberValue(double value){
		this->value = value;
	}

	int as_int(){
		return (int)as_number();
	}

	double as_number(){
		return value;
	}
	
	std::string as_string(){
		return func::dtos(value);
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