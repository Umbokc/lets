#ifndef ASSIGNMENT_STATEMENT_CPP
#define ASSIGNMENT_STATEMENT_CPP
#include <string>

class AssignmentStatement : public Statement{
public:
	std::string variable;
	Expression* expression;

	AssignmentStatement(std::string variable, Expression* expression){
		this->variable = variable;
		this->expression = expression;
	}

	void execute(){
		Value* result = expression->eval();
		Variables::set(variable, result);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return variable + " = " + expression->to_s();
	}

	~AssignmentStatement(){
		// delete[] expression;
	}
};
#endif
