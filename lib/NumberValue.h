#ifndef NUMBERVALUE
#define NUMBERVALUE
class NumberValue : public Value{
	double value;
public:
	NumberValue(double value){
		this->value = value;
	}

	double asDouble(){
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