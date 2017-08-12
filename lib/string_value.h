#ifndef STRING_VALUE_H
#define STRING_VALUE_H

#include <string>
#include <cstdlib>

class StringValue : virtual public Value{
private:
	std::string value;
public:

	StringValue(std::string value){
		this->value = value;
	}

	int as_int(){
		return (int)as_number();
	}

	double as_number(){
		return atof(&value[0u]);
	}

	long long as_long(){
		return std::stol(&value[0u], 0);
	}
	
	std::string get_c(int index){
		return func::ctos(value[index]);
	}
	
	std::string as_string(){
		return value;
	}
	
	std::string to_s(){
		return as_string();
	}
	
	Types type(){
		return Types::T_STRING;
	}

	~StringValue(){
		
	}
	
};
#endif