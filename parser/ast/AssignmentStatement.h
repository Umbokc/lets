#ifndef ASSIGNMENTSTATEMENT_H
#define ASSIGNMENTSTATEMENT_H

AssignmentStatement::AssignmentStatement(std::string variable, Expression *expression){
	this->variable = variable;
	this->expression = expression;
}

void AssignmentStatement::execute(){
	Value* result = expression->eval();
	Variables::set(variable, result);
}

void AssignmentStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string AssignmentStatement::to_s(){
	return variable + " = " + expression->to_s();
}

#endif
