//
//  include/lib/property.hpp
//  lets
//
//  Created by Dragan Stepan on 21.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__lib__property_hpp
#define include__lib__property_hpp

#include <string>
#include "../main.h"

class Property{
public:
	Value *value;
	bool is_private;
	bool is_constant;

	Property();

	Property(Value*);
	Property(Value*, bool, bool);
	lets_str_t to_s();
	~Property();
};

#endif /* include__lib__property_hpp */

