#ifndef VALUEEXPRESSION_H
#define VALUEEXPRESSION_H

ValueExpression::ValueExpression(double value){
	this->value = new NumberValue(value);
}

ValueExpression::ValueExpression(std::string value){
	this->value = new StringValue(value);
}

Value* ValueExpression::eval(){
	return value;
}

void ValueExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ValueExpression::to_s(){
	return value->asString();
}

#endif
