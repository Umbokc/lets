#ifndef EXPRESSION_H
#define EXPRESSION_H

class Expression{
public:
	virtual Value* eval() = 0;
	virtual std::string to_s() = 0;
};

#endif
