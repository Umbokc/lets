#ifndef VALUEEXPRESSION
#define VALUEEXPRESSION
#include <sstream>

class ValueExpression : public Expression{
private:
	Value* value;
public:

	ValueExpression(double value){
		this->value = new NumberValue(value);
	}

	ValueExpression(std::string value){
		this->value = new StringValue(value);
	}

	Value* eval(){
		return value;
	}

	std::string to_s(){
		return value->asString();
	}
};

#endif
