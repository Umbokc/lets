#ifndef NUMBERVALUE_H
#define NUMBERVALUE_H
class NumberValue : public Value{
	double value;
public:

	NumberValue(double value){
		this->value = value;
	}

	double asNumber(){
		return value;
	} 
	
	std::string asString(){
		return dtos(value);
	} 
	
	std::string to_s(){
		return asString();
	}

	~NumberValue();
	
};
#endif