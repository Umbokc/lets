#ifndef PUT_STATEMENT_H
#define PUT_STATEMENT_H

#include <iostream>

class PutStatement : public Statement{
public:
	Expression *expression;

	PutStatement(Expression *expression)
				:expression(std::move(expression))
	{}

	void execute(){
		std::cout << expression->eval()->to_s();
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return "put " + expression->to_s();
	}

	~PutStatement(){
		// delete[] expression;
	}
};

#endif
