#ifndef PRINTSTATEMENT_H
#define PRINTSTATEMENT_H

using namespace std;

PrintStatement::PrintStatement(Expression *expression){
	this->expression = expression;
}

void PrintStatement::execute(){
		cout << expression->eval()->to_s();
}

void PrintStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string PrintStatement::to_s(){
	return "print " + expression->to_s();
}

#endif
