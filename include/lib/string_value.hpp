//
//  include/lib/string_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__string_value_hpp
#define include__lib__string_value_hpp

#include "value.hpp"

class StringValue : virtual public Value{
private:
	lets_str_t value;
public:

	StringValue();
	StringValue(char);
	StringValue(lets_str_t);

	LETS_REQUIRED_METHODS_VALUE_DECL()

	lets_str_t get_c(int);

	bool has(Value*);
	bool has(Value*, int);

	~StringValue();
};

#endif /* include__lib__string_value_hpp */
