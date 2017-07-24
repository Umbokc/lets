#ifndef NODE_H
#define NODE_H

#include "visitor.h"

class Node {
public:
	virtual void accept(Visitor *visitor) = 0;
};

#endif
