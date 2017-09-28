#ifndef VARIABLE_CONTAINER_H
#define VARIABLE_CONTAINER_H

#include <string>
#include "value.h"

class VariableContainer {
private:
public:
	Value *value;
	bool is_constant;

	VariableContainer(Value *value) : value(std::move(value)){
		is_constant = false;
	}

	VariableContainer(Value *value, bool is_const):
		value(std::move(value)),
		is_constant(std::move(is_const))
	{}

	~VariableContainer(){}
};

#endif