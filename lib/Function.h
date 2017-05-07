#ifndef FUNCTION_H
#define FUNCTION_H

class Function {
public:
	virtual Value* execute(std::vector<Value *> args) = 0;
};

#endif