//
//  include/lib/function_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__function_value_hpp
#define include__lib__function_value_hpp

#include "../main.h"
#include "function.h"

class FunctionValue : public Value{
	Function* value;
public:

	FunctionValue();
	FunctionValue(Function*);

	Function* get_value();

	LETS_REQUIRED_METHODS_VALUE_DECL();

	~FunctionValue();
};

#endif /* include__lib__function_value_hpp */
