//
//  include/lib/bool_value.hpp
//  lets
//
//  Created by Dragan Stepan on 27.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__bool_value_hpp
#define include__lib__bool_value_hpp

#include "value.h"

class BoolValue : public Value{
private:
public:
	bool value;
	static BoolValue* TRUE;
	static BoolValue* FALSE;

	BoolValue(bool);
	BoolValue(NumberValue*);
	BoolValue(StringValue*);
	BoolValue(ArrayValue*);
	BoolValue(MapValue*);

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

	~BoolValue();
};

#endif /* include__lib__bool_value_hpp */

