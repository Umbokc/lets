#ifndef FUNCTION_STATEMENT_H
#define FUNCTION_STATEMENT_H

class FunctionStatement : public Statement{
public:
	FunctionalExpression *function;

	FunctionStatement(FunctionalExpression *function):
		function(std::move(function))
	{}

	void execute(){
		function->eval();
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return function->to_s();
	}

	~FunctionStatement(){
		delete[] function;
	}
};

#endif
