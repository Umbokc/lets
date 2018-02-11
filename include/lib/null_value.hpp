//
//  include/lib/null_value.hpp
//  lets
//
//  Created by Dragan Stepan on 27.01.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__lib__null_value_hpp
#define include__lib__null_value_hpp

#include "value.h"

class NullValue : public Value{
private:
public:

	static NullValue *THE_NULL;

	NullValue();

	bool as_bool();
	int as_int();
	double as_number();
	long as_long();

	int len();
	Types type();

	lets_str_t as_string();
	lets_str_t to_s();

	bool equals(Value*);
	int compareTo(Value*);

	~NullValue();
};

#endif /* include__lib__null_value_hpp */

