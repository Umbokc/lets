#ifndef VALUE_EXPRESSION_CPP
#define VALUE_EXPRESSION_CPP
#include <string>

class ValueExpression : public Expression {
public:
	Value *value;

	ValueExpression(){}

	ValueExpression(int value){
		this->value = new NumberValue(value);
	}

	ValueExpression(double value){
		this->value = new NumberValue(value);
	}

	ValueExpression(long value){
		this->value = new NumberValue(value);
	}

	ValueExpression(std::string value){
		this->value = new StringValue(value);
	}

	ValueExpression(Function *value){
		this->value = new FunctionValue(value);
	}

	ValueExpression(Value *value):value(std::move(value)){}

	Value *eval(){
		return value;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return value->as_string();
	}

	~ValueExpression(){}
};

#endif