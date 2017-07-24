#ifndef PRINTLN_STATEMENT_H
#define PRINTLN_STATEMENT_H

#include <iostream>

class PrintlnStatement : public Statement{
public:
	Expression *expression;

	PrintlnStatement(Expression *expression)
				:expression(std::move(expression))
	{}

	void execute(){
		cout << expression->eval()->to_s() << std::endl;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return "println " + expression->to_s();
	}

	~PrintlnStatement(){
		// delete[] expression;
	}
};

#endif
