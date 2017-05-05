#ifndef UNARYEXPRESSION
#define UNARYEXPRESSION

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
		switch(operation){
			case '-' : return new NumberValue(-expr1->eval()->asDouble());
			case '+' :
				default: return expr1->eval();
		}
	}

	std::string to_s(){ 
		return operation + expr1->to_s();
	}
	~UnaryExpression();
};

UnaryExpression::~UnaryExpression(){
	// delete[] expr1;
}

#endif
