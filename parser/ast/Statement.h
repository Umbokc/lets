#ifndef STATEMENT
#define STATEMENT

class Statement{
public:
	virtual void execute() = 0; 
	virtual std::string to_s() = 0;
};

#endif