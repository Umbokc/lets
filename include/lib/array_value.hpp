//
//  include/lib/array_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__array_value_hpp
#define include__lib__array_value_hpp

#include <vector>
#include <string>
#include "../main.h"
#include "value.h"

class ArrayValue : public Value{
	lets_vector_t<Value *> elements;
public:

	ArrayValue(int);
	ArrayValue(Value*);
	ArrayValue(lets_vector_t<Value *> );
	ArrayValue(ArrayValue *);

	void add(Value *);
	void add_forward(Value *);

	Value *get(int);
	Value *get_always(int);
	lets_vector_t<Value *> get_all();

	bool has(Value*);
	bool has(Value*, int);

	void set(int , Value *);

	bool as_bool();
	int as_int();
	double as_number();
	long as_long();
	int len();
	int size();

	lets_str_t as_string();
	lets_str_t to_s();
	Types type();

	bool equals(Value* );
	int compareTo(Value *);

	~ArrayValue();
};

namespace NS_ArrayValue{
	ArrayValue *add(ArrayValue *arr, Value *value);
	ArrayValue *add_forward(ArrayValue *arr, Value *value);
	ArrayValue *merge(ArrayValue *value1, ArrayValue *value2);
};

#endif /* include__lib__array_value_hpp */
