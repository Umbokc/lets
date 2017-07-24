#ifndef RETURN_STATEMENT_H
#define RETURN_STATEMENT_H
#include <string>

class ReturnStatement : public Statement{
public:
	Value *result;
	Expression *expression;

	ReturnStatement(Expression *expression){
		this->expression = expression;
	}

	Value *get_result(){
		return result;
	}

	void execute(){
		result = expression->eval();
		throw this;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return "return";
	}

	~ReturnStatement(){
		// delete[] result;
		// delete[] expression;
	}

};

#endif