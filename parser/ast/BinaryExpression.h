#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

BinaryExpression::BinaryExpression(char o, Expression *e1, Expression *e2){
	operation = o;
	expr1 = e1;
	expr2 = e2;
}

Value * BinaryExpression::eval(){
	Value *value1 = expr1->eval();
	Value *value2 = expr2->eval();

	if(isStringValue(value1) || isArrayValue(value1)){
		// if(Value* v1 = dynamic_cast<StringValue*>(value1)){
		std::string string1 = value1->asString();
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

void BinaryExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string BinaryExpression::to_s(){ 
	return "[" + expr1->to_s() + " " + operation + " " + expr2->to_s() + "]";
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
