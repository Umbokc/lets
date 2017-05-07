#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

class BinaryExpression : public Expression{
private:
	Expression *expr1;
	Expression *expr2;
	char operation;
public:

	BinaryExpression(char o, Expression *e1, Expression *e2){
		operation = o;
		expr1 = e1;
		expr2 = e2;
	}

	Value * eval(){
		Value *value1 = expr1->eval();
		Value *value2 = expr2->eval();

		if(Value* v1 = dynamic_cast<StringValue*>(value1)){
			std::string string1 = v1->asString();
			switch(operation){
				case '*' :{
					int iteration = (int) value2->asNumber();
					std::string buffer = string1;
					for (int i = 0; i < iteration; ++i){
						buffer += string1;
					}
					return new StringValue(buffer);
				}
				case '+' :
				default: return new StringValue(string1 + value2->asString());
			}
		}
		
		double e1 = value1->asNumber();
		double e2 = value2->asNumber();

		switch(operation){
			case '*' : return new NumberValue(e1 * e2);
			case '/' : return new NumberValue(e1 / e2);
			case '-' : return new NumberValue(e1 - e2);
			case '+' :
			default: return new NumberValue(e1 + e2);
		}
		
	}

	std::string to_s(){ 
		return "[" + expr1->to_s() + " " + operation + " " + expr2->to_s() + "]";
	}
	~BinaryExpression();
};

BinaryExpression::~BinaryExpression(){
	delete[] expr1;
	delete[] expr2;
}

#endif
