//
//  include/lib/class_value.hpp
//  lets
//
//  Created by Dragan Stepan on 11.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//
#ifndef include__lib__class_value_hpp
#define include__lib__class_value_hpp

#include "value.hpp"

class ClassValue : public Value{
public:

	ClassValue();
	// ClassValue(Class*);

	LETS_REQUIRED_METHODS_VALUE_DECL()

	~ClassValue();
};

#endif /* include__lib__class_value_hpp */