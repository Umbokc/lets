#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H

ReturnStatement::ReturnStatement(Expression *expression){
	this->expression = expression;
}

Value *ReturnStatement::getResult(){
	return result;
}

void ReturnStatement::execute(){
	result = expression->eval();
	throw this;
}

void ReturnStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ReturnStatement::to_s(){
	std::string result("return");
	return result;
}

#endif
