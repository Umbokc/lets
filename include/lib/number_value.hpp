//
//  include/lib/number_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__number_value_hpp
#define include__number_value_hpp

#include "value.hpp"
#include "number.hpp"

class NumberValue : public Value{
private:
public:
	Number* value;
	static NumberValue* ZERO;
	static NumberValue* ONE;
	static NumberValue* NEGATE_ONE;

	NumberValue();
	NumberValue(int);
	NumberValue(double);
	NumberValue(long);
	NumberValue(Number*);

	Number* get_value();

	LETS_REQUIRED_METHODS_VALUE_DECL()

	~NumberValue();
};

#endif /* include__number_value_hpp */
