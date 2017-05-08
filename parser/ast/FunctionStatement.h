#ifndef FUNCTIONSTATEMENT_H
#define FUNCTIONSTATEMENT_H

FunctionStatement::FunctionStatement(FunctionalExpression *function){
	this->function = function;
}

void FunctionStatement::execute(){
	function->eval();
}

void FunctionStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string FunctionStatement::to_s(){
	return function->to_s();
}

#endif
