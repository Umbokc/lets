#ifndef VALUE_EXPRESSION_CPP
#define VALUE_EXPRESSION_CPP
#include <string>

class ValueExpression : virtual public Expression {
public:
	Value *value;

	ValueExpression(){}

	ValueExpression(double value){
		this->value = new NumberValue(value);
	}

	ValueExpression(std::string value){
		this->value = new StringValue(value);
	}

	Value *eval(){
		return value;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return value->as_string();
	}

	~ValueExpression(){}
};

#endif