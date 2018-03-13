//
//  include/node.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__node_h
#define include__node_h

// #include <iostream> // for dbg
// #include "main.h" // for dbg

#include "visitors/visitor.h"
#include "visitors/result_visitor.h"

#define LETS_VISITORS_FUCTION_ACCEPT_MACROS() \
	void accept(Visitor* v){ \
		v->visit(this); \
	} \
	template <class R, class T> \
	R accept(ResultVisitor<R, T> *visitor, T& t){ \
		return visitor->visit(this, t); \
	}

class Node {
protected:
	size_t __node__row = 1;
	size_t __node__col = 1;
public:
	void set_position(const size_t& r, const size_t& c){ __node__row = r; __node__col = c; }
	const lets_str_t get_position() const { return to_str(__node__row) + ":" + to_str(__node__col); }
	const size_t get_position_row() const { return __node__row;}
	const size_t get_position_col() const { return __node__col;}

	virtual void accept(Visitor*) = 0;

	template <class R, class T>
	R accept(ResultVisitor<R, T> *visitor, T& t){
		return visitor->visit(this, t);
	}

	virtual ~Node() {}
};

#endif /* include__node_h */
