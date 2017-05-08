#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

UnaryExpression::UnaryExpression(Operator operation, Expression *expr1){
	this->operation = operation;
	this->expr1 = expr1;
}

Value* UnaryExpression::eval(){
	Value* value = expr1->eval();
	switch(operation){
		case NEGATE: return new NumberValue(-value->asNumber());
		case COMPLEMENT: return new NumberValue(~(int)value->asNumber());
		case NOT: return new NumberValue(value->asNumber() != 0 ? 0 : 1);
		default:
			error("Operation " + OperatorText[operation] + " is not supported");
	}
	
}

void UnaryExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string UnaryExpression::to_s(){
	return "[" + OperatorText[operation] + expr1->to_s() + "]";
}

#endif
