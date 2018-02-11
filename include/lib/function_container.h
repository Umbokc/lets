//
//  include/lib/function_container.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__function_container_h
#define include__lib__function_container_h

#include "function.h"

class FunctionContainer {
private:
public:
	Function* body;
	bool is_constant;

	FunctionContainer(Function *body) : body(std::move(body)) {
		is_constant = false;
	}

	FunctionContainer(Function *body, bool is_const):
	body(std::move(body)), is_constant(std::move(is_const)){}

	~FunctionContainer(){}

};

#endif /* include__lib__function_container_h */
