//
//  include/lib/string_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__string_value_hpp
#define include__lib__string_value_hpp

#include "value.h"

class StringValue : virtual public Value{
private:
	lets_str_t value;
public:

	StringValue();
	StringValue(char);
	StringValue(lets_str_t);

	bool as_bool();
	int as_int();
	double as_number();
	long as_long();

	lets_str_t get_c(int);

	bool has(Value*);
	bool has(Value*, int);

	int len();
	lets_str_t as_string();
	lets_str_t to_s();

	Types type();

	bool equals(Value*);
	int compareTo(Value*);

	~StringValue();
};

#endif /* include__lib__string_value_hpp */