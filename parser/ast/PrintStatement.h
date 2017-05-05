#ifndef PRINTSTATEMENT
#define PRINTSTATEMENT

class PrintStatement : public Statement{
private:
	Expression *expression;
public:
	PrintStatement(Expression *expression){
		this->expression = expression;
	}

	void execute(){
 		cout << expression->eval()->to_s();
	}
	
	std::string to_s(){
		return "print " + expression->to_s();
	}

	~PrintStatement();
};
#endif
