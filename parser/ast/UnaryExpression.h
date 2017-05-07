#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

class UnaryExpression : public Expression{
private:
	Expression *expr1;
	char operation;
public:

	UnaryExpression(char o, Expression *e1){
		operation = o;
		expr1 = e1;
	}

	Value* eval(){
		Value* value1 = expr1->eval();
		switch(operation){
			case '-' : return new NumberValue(-value1->asNumber());
			case '+' :
			default: return value1;
		}
		
	}

	std::string to_s(){
		return "[" + ctos(operation) + expr1->to_s() + "]";
	}
	~UnaryExpression();
};

UnaryExpression::~UnaryExpression(){
	delete[] expr1;
}

#endif
