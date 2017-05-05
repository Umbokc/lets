#ifndef EXPRESSION
#define EXPRESSION

class Expression{
public:
	virtual Value* eval() = 0;
	virtual std::string to_s() = 0;
};

#endif
