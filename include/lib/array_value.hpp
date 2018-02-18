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
#include "value.hpp"

class ArrayValue : public Value{
	lets_vector_t<Value *> elements;
public:

	ArrayValue();
	ArrayValue(int);
	ArrayValue(Value*);
	ArrayValue(lets_vector_t<Value *>);
	ArrayValue(ArrayValue *);

	LETS_REQUIRED_METHODS_VALUE_DECL()

	ArrayValue* create_array(Value*,FUNCS_ARGS,int);

	void add(Value *);
	void add_forward(Value *);

	Value *get(int);
	Value *get_always(int);
	lets_vector_t<Value *> get_all();

	bool has(Value*);
	bool has(Value*, int);

	void set(int , Value *);

	int size();

	~ArrayValue();
};

namespace NS_ArrayValue{
	ArrayValue *add(ArrayValue *arr, Value *value);
	ArrayValue *add_forward(ArrayValue *arr, Value *value);
	ArrayValue *merge(ArrayValue *value1, ArrayValue *value2);
};

#endif /* include__lib__array_value_hpp */
