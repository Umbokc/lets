#ifndef CONTINUESTATEMENT_H
#define CONTINUESTATEMENT_H


ContinueStatement::ContinueStatement(){
}

void ContinueStatement::execute(){
	throw this;
}

void ContinueStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ContinueStatement::to_s(){
	std::string result("continue");
	return result;
}

#endif
