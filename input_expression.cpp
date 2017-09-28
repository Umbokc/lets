#ifndef INPUT_EXPRESSION_CPP
#define INPUT_EXPRESSION_CPP
#include <string>

class InputExpression : virtual public Expression {
public:

	Value *value;

	InputExpression(){
	}

	Value *eval(){
		std::string str;
		getline(std::cin, str);
		// std::cin >> str;
		this->value = new StringValue(str);
		return value;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return value->as_string();
	}

	~InputExpression(){}
};

#endif