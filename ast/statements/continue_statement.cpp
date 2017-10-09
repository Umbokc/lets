#ifndef CONTINUE_STATEMENT_H
#define CONTINUE_STATEMENT_H

class ContinueStatement : public Statement{
public:

	ContinueStatement(){
	}

	void execute(){
		throw this;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return "continue";
	}

	~ContinueStatement(){}
};

#endif
