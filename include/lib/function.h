//
//  include/lib/function.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__function_h
#define include__lib__function_h

#include <string>
#include <map>
#include <vector>
#include "../main.h"
#include "value.h"
#include "../expression.h"

class Function {
public:
	virtual Value* execute(FUNCS_ARGS) = 0;
	virtual lets_str_t to_s() = 0;
};

#endif /* include__lib__function_h */
