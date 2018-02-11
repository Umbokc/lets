//
//  include/lib/number_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__number_value_hpp
#define include__number_value_hpp

#include "value.h"
#include "number.hpp"

class NumberValue : public Value{
private:
public:
	Number value;
	static NumberValue* ZERO;
	static NumberValue* ONE;
	static NumberValue* NEGATE_ONE;

	NumberValue(int);
	NumberValue(double);
	NumberValue(long);
	NumberValue(Number);

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

	~NumberValue();
};

#endif /* include__number_value_hpp */
