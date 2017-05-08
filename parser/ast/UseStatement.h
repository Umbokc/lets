#ifndef USESTATEMENT_H
#define USESTATEMENT_H

UseStatement::UseStatement(Expression *expression){
	this->expression = expression;
}

void UseStatement::execute(){

}

void UseStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string UseStatement::to_s(){
	return "[" + ctos(operation) + expr1->to_s() + "]";
}

#endif
