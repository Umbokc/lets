#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>

class Function {
public:
	virtual Value* execute(std::vector<Value *> args) = 0;
	virtual std::string to_s() = 0;
};

#endif