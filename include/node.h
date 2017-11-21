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
protected:
	size_t __node__row = 1;
	size_t __node__col = 1;
public:
	void set_position(size_t r, size_t c){
		__node__row = r;
		__node__col = c;
	}
	lets_str_t get_position(){ return to_str(__node__row) + ":" + to_str(__node__col); }
	const size_t get_position_row() const { return __node__row;}
	const size_t get_position_col() const { return __node__col;}

	template <class C>
	void accept(C s, Visitor* v){
		v->visit(s);
	}

	template <class C, class R, class T>
	R accept(C s, ResultVisitor<R, T> *visitor, T t){
		return visitor->visit(s, t);
	}

	virtual ~Node() {}
};

#endif /* node_h */
