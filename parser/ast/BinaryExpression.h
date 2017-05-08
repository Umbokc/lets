#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

BinaryExpression::BinaryExpression(Operator operation, Expression *expr1, Expression *expr2){
	this->operation = operation;
	this->expr1 = expr1;
	this->expr2 = expr2;
}

Value * BinaryExpression::eval(){
	Value *value1 = expr1->eval();
	Value *value2 = expr2->eval();

	if(isStringValue(value1) || isArrayValue(value1)){
		// if(Value* v1 = dynamic_cast<StringValue*>(value1)){
		std::string string1 = value1->asString();
		switch(operation){
			case MULTIPLY :{
				int iteration = (int) value2->asNumber();
				std::string buffer = string1;
				for (int i = 0; i < iteration; ++i){
					buffer += string1;
				}
				return new StringValue(buffer);
			}
			case ADD :
			default: return new StringValue(string1 + value2->asString());
		}
	}
	
	double number1 = value1->asNumber();
	double number2 = value2->asNumber();

	double result;
	switch(operation){
		case ADD: result = number1 + number2; break;
		case SUBTRACT: result = number1 - number2; break;
		case MULTIPLY: result = number1 * number2; break;
		case DIVIDE: result = number1 / number2; break;
		case REMAINDER: result = (int)number1 % (int)number2; break;

		// Bitwise
		case AND: result = (int)number1 & (int)number2; break;
		case XOR: result = (int)number1 ^ (int)number2; break;
		case OR: result = (int)number1 | (int)number2; break;
		case LSHIFT: result = (int)number1 << (int)number2; break;
		case RSHIFT: result = (int)number1 >> (int)number2; break;
		// case URSHIFT: result = (int)number1 >>> (int)number2; break;

		default:
			error("Operation " + OperatorText[operation] + " is not supported");
	}
	return new NumberValue(result);
}

void BinaryExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string BinaryExpression::to_s(){ 
	return "[" + expr1->to_s() + " " + OperatorText[operation] + " " + expr2->to_s() + "]";
}

bool BinaryExpression::isArrayValue(Value *value){
	Value *v1;
	return (v1 = dynamic_cast<ArrayValue*>(value));
}
bool BinaryExpression::isStringValue(Value *value){
	Value *v1;
	return (v1 = dynamic_cast<StringValue*>(value));
}

#endif
