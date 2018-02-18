//
//  include/accessible.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__accessible_h
#define include__accessible_h

#include "main.h"
#include "node.h"
#include "lib/value.hpp"

class Accessible : virtual public Node {
public:
	virtual Value* get() = 0;
	virtual Value* set(Value* value) = 0;
	virtual lets_str_t to_s() = 0;
};


#endif /* include__accessible_h */
