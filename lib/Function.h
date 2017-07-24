#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>

class Function {
public:
	virtual Value* execute(std::vector<Value *> args) = 0;
};

#endif