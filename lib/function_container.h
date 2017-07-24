#ifndef FUNCTION_CONTAINER_H
#define FUNCTION_CONTAINER_H

#include <string>
#include "function.h"

class FunctionContainer {
private:
public:
	Function* body;
	bool is_constant;

	FunctionContainer(Function *body) : body(std::move(body)) {
		is_constant = false;
	}

	FunctionContainer(Function *body, bool is_const):
		body(std::move(body)), is_constant(std::move(is_const))
	{}

	~FunctionContainer(){}
};

#endif