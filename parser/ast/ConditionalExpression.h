#ifndef CONDITIONALEXPRESSION_H
#define CONDITIONALEXPRESSION_H

ConditionalExpression::ConditionalExpression(Operator operation, Expression *expr1, Expression *expr2){
	this->operation = operation;
	this->expr1 = expr1;
	this->expr2 = expr2;
}

Value* ConditionalExpression::eval(){
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

void ConditionalExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ConditionalExpression::to_s(){ 
	return "[" + expr1->to_s() + " " + OperatorText[operation] + " " + expr2->to_s() + "]";
}



#endif
