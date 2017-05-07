#ifndef CONDITIONALEXPRESSION_H
#define CONDITIONALEXPRESSION_H

std::string OperatorText[] =  { 
	"+",
	"-",
	"*",
	"/",

	"==",
	"!=",

	"<",
	"<=",
	">",
	">=",

	"&&",
	"||"
};

class ConditionalExpression : public Expression{
public:
	static enum Operator {
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,

		EQUALS,
		NOT_EQUALS,

		LT,
		LTEQ,
		GT,
		GTEQ,

		AND,
		OR
	} x;
private:
	Expression *expr1;
	Expression *expr2;
	Operator operation;
public:

	ConditionalExpression(Operator o, Expression *e1, Expression *e2){
		operation = o;
		expr1 = e1;
		expr2 = e2;
	}

	Value* eval(){
		Value* value1 = expr1->eval();
		Value* value2 = expr2->eval();


		double number1, number2;

		if(Value* v1 = dynamic_cast<StringValue*>(value1)){
			number1 = compareTo(value1->asString(), value2->asString());
			number2 = 0;
		} else {
			number1 = value1->asNumber();
			number2 = value2->asNumber();
		}

		bool result;

		switch(operation){
			case LT : result = (number1 < number2); break;
			case LTEQ : result = (number1 <= number2); break;
			case GT : result = (number1 > number2); break;
			case GTEQ : result = (number1 >= number2); break;
			case NOT_EQUALS : result = (number1 != number2); break;	

			case AND : result = (number1 != 0 && number2 != 0); break;	
			case OR : result = (number1 != 0 || number2 != 0); break;	
			
			case EQUALS :
			default: 
				result = (number1 == number2); break;
		}

		return new NumberValue(result);
	}

	std::string to_s(){ 
		return "[" + expr1->to_s() + " " + OperatorText[operation] + " " + expr2->to_s() + "]";
	}
	~ConditionalExpression();
};

ConditionalExpression::~ConditionalExpression(){
	// delete[] expr1;
	// delete[] expr2;
}

#endif
