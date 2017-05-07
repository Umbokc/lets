#ifndef FUNCTIONSTATEMENT_H
#define FUNCTIONSTATEMENT_H

class FunctionStatement : public Statement{
private:
	FunctionalExpression *function;
public:

	FunctionStatement(FunctionalExpression *function){
		this->function = function;
	}

	void execute(){
		function->eval();
	}
	
	std::string to_s(){
		return function->to_s();
	}

	~FunctionStatement();
};
#endif
