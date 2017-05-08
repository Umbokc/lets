#ifndef ARRAYEXPRESSION_H
#define ARRAYEXPRESSION_H

ArrayExpression::ArrayExpression(std::vector<Expression *> elements){
	this->elements = elements;
}

Value *ArrayExpression::eval(){
		// ArrayValue *array = new ArrayValue(elements);

	int size = elements.size();
	ArrayValue *array = new ArrayValue(size);

	for (int i = 0; i < size; i++) {
		array->set(i, elements[i]->eval());
	}

	return array;
}

void ArrayExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ArrayExpression::to_s(){
	std::string result = "[ ";
	
	for (Expression *argument : elements){
		result += argument->to_s();
		result +=  ", ";
	}

	result +=  "\b\b ]";

	return result;
}

#endif
