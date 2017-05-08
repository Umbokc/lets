#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

UnaryExpression::UnaryExpression(char o, Expression *e1){
	operation = o;
	expr1 = e1;
}

Value* UnaryExpression::eval(){
	Value* value1 = expr1->eval();
	switch(operation){
		case '-' : return new NumberValue(-value1->asNumber());
		case '+' :
		default: return value1;
	}
	
}

void UnaryExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string UnaryExpression::to_s(){
	return "[" + ctos(operation) + expr1->to_s() + "]";
}

#endif
