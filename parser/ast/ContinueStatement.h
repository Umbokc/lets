#ifndef CONTINUESTATEMENT_H
#define CONTINUESTATEMENT_H

class ContinueStatement : public Statement{
private:
public:

	ContinueStatement(){
	}

	void execute(){
		throw this;
	}
	
	std::string to_s(){
		std::string result("continue");
		return result;
	}

	~ContinueStatement();
};
#endif
