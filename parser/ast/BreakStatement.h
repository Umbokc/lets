#ifndef BREAKSTATEMENT_H
#define BREAKSTATEMENT_H

BreakStatement::BreakStatement(){
}

void BreakStatement::execute(){
	throw this;
}

void BreakStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string BreakStatement::to_s(){
	std::string result("break");
	return result;
}

#endif
