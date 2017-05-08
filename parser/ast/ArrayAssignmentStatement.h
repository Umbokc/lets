#ifndef ARRAYASSIGNMENTSTATEMENT_H
#define ARRAYASSIGNMENTSTATEMENT_H

ArrayAssignmentStatement::ArrayAssignmentStatement(ArrayAccessExpression *array, Expression *expression){
	this->array = array;
	this->expression = expression;
}

void ArrayAssignmentStatement::execute(){
	array->getArray()->set(array->lastIndex(),expression->eval());
}

void ArrayAssignmentStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ArrayAssignmentStatement::to_s(){
	return array->to_s() + " = " + expression->to_s();
}

#endif
