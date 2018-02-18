//
//  include/lib/null_value.hpp
//  lets
//
//  Created by Dragan Stepan on 27.01.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__lib__null_value_hpp
#define include__lib__null_value_hpp

#include "value.hpp"

class NullValue : public Value{
public:
	static NullValue *THE_NULL;

	NullValue();

	LETS_REQUIRED_METHODS_VALUE_DECL()

	~NullValue();
};

#endif /* include__lib__null_value_hpp */

