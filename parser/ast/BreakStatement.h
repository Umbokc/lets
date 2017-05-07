#ifndef BREAKSTATEMENT_H
#define BREAKSTATEMENT_H

class BreakStatement : public Statement{
private:
public:

	BreakStatement(){
	}

	void execute(){
		throw this;
	}
	
	std::string to_s(){
		std::string result("break");
		return result;
	}

	~BreakStatement();
};
#endif
