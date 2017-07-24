#ifndef STATEMENT_H
#define STATEMENT_H

class Statement : public Node
{
public:
	virtual void execute() = 0; 
	virtual std::string to_s() = 0;
};

#endif