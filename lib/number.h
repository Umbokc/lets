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

	NS_Number::evil as_num(){ return this->val; }
	
	int as_int(){
		return static_cast<int>(
				(is_double()) ? this->val.d :
				(is_long()) ? this->val.l :
				this->val.i
		);
	}

	double as_double(){
		return static_cast<double>(
				(is_int()) ? this->val.i :
				(is_long()) ? this->val.l :
				this->val.d
		);
	}

	long as_long(){
		return static_cast<long>(
				(is_int()) ? this->val.i :
				(is_double()) ? this->val.d :
				this->val.l
		);
	}

	bool is_int(){ return (type == NS_Number::types::TYPE_INT); }
	bool is_double(){ return (type == NS_Number::types::TYPE_DOUBLE); }
	bool is_long(){ return (type == NS_Number::types::TYPE_LONG); }
	
	std::string as_string(){
		return func::number_to_s((is_double()) ? this->val.d : (is_long()) ? this->val.l : this->val.i);
	}
	
	std::string to_s(){
		return as_string();
	}

	~Number(){}
	
};
#endif