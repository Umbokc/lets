#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include <limits>
#include <cmath>

namespace NS_Number {
	typedef union {
		int i;
		double d;
		long l;
	} evil;

	typedef enum {
		TYPE_INT, TYPE_DOUBLE, TYPE_LONG
	} types;
}

class Number {
	NS_Number::evil val;
	NS_Number::types type;
public:
	
	Number(){}

	Number& operator=(const Number& n){ return *this; }
	
	void operator=(int value){ add(value); }
	void operator=(double value){ add(value); }
	void operator=(long value){ add(value); }

	Number(int& value){ add(value); }
	Number(double& value){ add(value); }
	Number(long& value){ add(value); }

	template<class T>
	void add(T value){
		if(typeid(value) == typeid(int)){
			this->val.i = value;
			this->type = NS_Number::types::TYPE_INT;
		} else if(typeid(value) == typeid(double)){
			this->val.d = value;
			this->type = NS_Number::types::TYPE_DOUBLE;
		} else if(typeid(value) == typeid(long)){
			this->val.l = value;
			this->type = NS_Number::types::TYPE_LONG;
		} else {
			std::cout << "Unknow Error" << std::endl; exit(1);
		}
	}

	int as_int(){
		return as_number<int>();
	}

	double as_double(){
		return as_number<double>();
	}

	long as_long(){
		return as_number<long>();
	}

	template<typename T>
	T as_number(){
		switch(type){
			case NS_Number::types::TYPE_INT:
				return static_cast<T>(this->val.i);
			case NS_Number::types::TYPE_LONG:
				return static_cast<T>(this->val.l);
			case NS_Number::types::TYPE_DOUBLE:
			default:
				return static_cast<T>(this->val.d);
		}
	}

	bool is_int(){ return (type == NS_Number::types::TYPE_INT); }
	bool is_double(){ return (type == NS_Number::types::TYPE_DOUBLE); }
	bool is_long(){ return (type == NS_Number::types::TYPE_LONG); }
	
	std::string as_string(){
		return func::number_to_s(
			(is_double()) ? this->val.d : (is_long()) ? this->val.l : this->val.i
		);
	}
	
	std::string to_s(){
		return as_string();
	}

	~Number(){}
	
};
#endif