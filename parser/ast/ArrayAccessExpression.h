#ifndef ARRAYACCESSEXPRESSION_H
#define ARRAYACCESSEXPRESSION_H

ArrayAccessExpression::ArrayAccessExpression(std::string variable, std::vector<Expression*> indices){
	this->variable = variable;
	this->indices = indices;
}

Value * ArrayAccessExpression::eval(){
	return getArray()->get(lastIndex());
}

void ArrayAccessExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ArrayAccessExpression::to_s(){ 
		// return variable + "[" + index->to_s() + "]";

	std::string result = variable + "";
	
	for (Expression *index : indices){
		result += index->to_s();
		result +=  ", ";
	}

	result +=  "\b\b ";

	return result;
}

ArrayValue * ArrayAccessExpression::getArray(){
	ArrayValue *array = consumeArray(Variables::get(variable));

	int last = indices.size() - 1;
	for (int i = 0; i < last; ++i){
		array = consumeArray(array->get(index(i)));
	}
	return array;
}

int ArrayAccessExpression::lastIndex(){
	return index(indices.size() - 1);
}

int ArrayAccessExpression::index(int index){
	return (int)indices[index]->eval()->asNumber();
}

ArrayValue *ArrayAccessExpression::consumeArray(Value *value){
	if(Value *v = dynamic_cast<ArrayValue*>(value)){
		return dynamic_cast<ArrayValue*>(value);
	} else {
		throw std::runtime_error("Array expected");
	}
}


#endif
