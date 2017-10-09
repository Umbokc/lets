#ifndef LL_INCLUDE_NODE_H
#define LL_INCLUDE_NODE_H

#include "../utils/visitors/visitor.h"
#include "../utils/visitors/result_visitor.h"

class Node {
public:
	virtual void accept(Visitor *visitor) = 0;

	template<class R> R accept_r(ResultVisitor<R>* visitor);

	virtual ~Node(){}
};

#endif
