#ifndef ASSIGNMENTSTATEMENT
#define ASSIGNMENTSTATEMENT

class AssignmentStatement : public Statement{
private:
	std::string variable;
	Expression *expression;
public:
	AssignmentStatement(std::string variable, Expression *expression){
		this->variable = variable;
		this->expression = expression;
	}

	void execute(){
		Value* result = expression->eval();
		Variables::set(variable, result);
	}
	
	std::string to_s(){
		return variable + " = " + expression->to_s();
	}

	~AssignmentStatement();
};
#endif
