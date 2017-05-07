#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H

class ReturnStatement : public Statement{
private:
	Expression *expression;
	Value *result;
public:

	ReturnStatement(Expression *expression){
		this->expression = expression;
	}

	Value *getResult(){
		return result;
	}

	void execute(){
		result = expression->eval();
		throw this;
	}
	
	std::string to_s(){
		std::string result("return");
		return result;
	}

	~ReturnStatement();
};
#endif
