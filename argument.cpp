#ifndef ARGUMENT_CPP
#define ARGUMENT_CPP

#include <string>

class Argument {
private:
	std::string name;
	Expression *value_expr;
public:
	Argument(){}

	Argument(std::string name): name(std::move(name))
	{}

	Argument(std::string name, Expression* value_expr):
		name(std::move(name)),
		value_expr(std::move(value_expr))
	{
	}

	std::string get_name(){return name;}
	Expression *get_value_expr(){return value_expr;}

	std::string to_s(){
		return name + (value_expr == NULL ? "" : " = " + value_expr->to_s());
	}

	~Argument(){}
};
#endif