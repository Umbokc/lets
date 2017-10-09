#ifndef ACCESSIBLE_H
#define ACCESSIBLE_H

#include "node.h"
#include "expression.h"

class Accessible : virtual public Node {
public:
	virtual Value* get() = 0;
	virtual Value* set(Value* value) = 0;
	virtual std::string to_s() = 0;
};

// class AccessExpr : public Expression, public Accessible{};

#endif
