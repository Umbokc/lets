#ifndef NUMBER_H
#define NUMBER_H
#include <string>

class Number {
private:
	int i_value;
	double d_value;
	long long l_value;

	int is_the_number;
public:
	
	Number(){}
	Number& operator=(const Number& n){return *this;}

	Number(int& value):i_value(std::move(value)){
		is_the_number = 0;
	}
	
	Number(double& value):d_value(std::move(value)){
		is_the_number = 1;
	}

	Number(long long& value):l_value(std::move(value)){
		is_the_number = 2;
	}

	int as_int(){
		if(is_int()) return i_value;
		if(is_double()) return (int) as_double();
		return (int) as_long();
	}

	double as_double(){
		if(is_double()) return d_value;
		if(is_int()) return (double)as_int();
		return (double)as_long();
	}

	long long as_long(){
		if(is_long()) return l_value;
		if(is_int()) return (long long)as_int();
		return (long long)as_double();
	}

	bool is_int(){
		return (is_the_number == 0);
	}

	bool is_double(){
		return (is_the_number == 1);
	}

	bool is_long(){
		return (is_the_number == 2);
	}
	
	std::string as_string(){
		if(is_int()) return std::to_string(i_value);
		if(is_double()) return func::dtos(d_value);
		if(is_long()) return std::to_string(l_value);
		return "";
	}
	
	std::string to_s(){
		return as_string();
	}

	~Number(){}
	
};
#endif