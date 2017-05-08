#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

IfStatement::IfStatement(Expression *expression, Statement *ifStatement, Statement *elseStatement){
	this->expression = expression;
	this->ifStatement = ifStatement;
	this->elseStatement = elseStatement;
}

void IfStatement::execute(){
	double result = expression->eval()->asNumber();
	if(result != 0){
		ifStatement->execute();
	} else if(elseStatement != NULL){
		elseStatement->execute();
	}
}

void IfStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string IfStatement::to_s(){
	std::string result = "";
	result += "if ";
	result += expression->to_s();
	result += " ";
	result += ifStatement->to_s();
	if(elseStatement != NULL){
		result += "\nelse ";
		result += elseStatement->to_s();
	}

	return result;
}

#endif
