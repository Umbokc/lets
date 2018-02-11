//
//  include/lib/value.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__value_h
#define include__lib__value_h

#include "types.h"

class BoolValue;
class NullValue;
class NumberValue;
class StringValue;
class ArrayValue;
class MapValue;
class FunctionValue;

class Value {
public:

	virtual bool as_bool() = 0;
	virtual int as_int() = 0;
	virtual double as_number() = 0;
	virtual long as_long() = 0;
	virtual lets_str_t as_string() = 0;
	virtual lets_str_t to_s() = 0;
	virtual int len() = 0;
	virtual Types type() = 0;
	virtual bool equals(Value*) = 0;
	virtual int compareTo(Value *obj) = 0;

	//virtual ~Value();
};

#endif /* include__lib__value_h */
