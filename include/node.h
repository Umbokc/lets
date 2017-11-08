//
//  node.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef node_h
#define node_h

// #include <iostream> #include "main.h" // for dbg() 
#include "visitors/visitor.h"
#include "visitors/result_visitor.h"

class Node {
public:

	template <class C>
	void accept(C s, Visitor* v){
		v->visit(s);
	}

	template <class C, class R, class T>
	R accept(C s, ResultVisitor<R, T> *visitor, T t){
		// dbg(typeid(s).name())
		return visitor->visit(s, t);
	}

	virtual ~Node() {}
};


#endif /* node_h */
