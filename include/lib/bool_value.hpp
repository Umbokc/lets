//
//  include/lib/bool_value.hpp
//  lets
//
//  Created by Dragan Stepan on 27.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__bool_value_hpp
#define include__lib__bool_value_hpp

#include "value.hpp"

class BoolValue : public Value{
private:
public:
	bool value;
	static BoolValue* TRUE;
	static BoolValue* FALSE;

	BoolValue();
	BoolValue(bool);
	BoolValue(NumberValue*);
	BoolValue(StringValue*);
	BoolValue(ArrayValue*);
	BoolValue(MapValue*);

	LETS_REQUIRED_METHODS_VALUE_DECL()

	~BoolValue();
};

#endif /* include__lib__bool_value_hpp */

