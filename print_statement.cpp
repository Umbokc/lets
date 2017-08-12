#ifndef PRINT_STATEMENT_H
#define PRINT_STATEMENT_H

class PrintStatement : public Statement{
public:
	Expression *expression;

	PrintStatement(Expression *expression){
		this->expression = expression;
	}

	void execute(){
		std::cout << expression->eval()->to_s();
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return "print " + expression->to_s();
	}

	~PrintStatement(){
		// delete[] expression;
	}
};

#endif
