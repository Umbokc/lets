#ifndef BREAK_STATEMENT_H
#define BREAK_STATEMENT_H

class BreakStatement : public Statement{
public:

	BreakStatement(){
	}

	void execute(){
		throw this;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return "break";
	}
	
	~BreakStatement();
};

#endif
