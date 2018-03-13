//
//  lets/lib/classes.cpp
//  lets
//
//  Created by Dragan Stepan on 11.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

// #include <iostream> // for dbg
#include "../../include/lib/classes.hpp"
#include "../../include/lib/include_values.h"
#include "../../include/lib/variables.hpp"
#include "../../include/exception/error.h"
#include "../../include/exception/execute.h"
#include "../../include/tools.hpp"

lets_map_t<lets_str_t, Value*> Classes::classes = {
	{"Bool", new BoolValue()},
	{"Null", new NullValue()},
	{"Number", new NumberValue()},
	{"String", new StringValue()},
	{"Array", new ArrayValue()},
	{"Map", new MapValue()},

	// {"Class", new ClassValue()},
	// {"Function", new FunctionValue()},
};

bool Classes::is_exists(lets_str_t key){
	return classes.find(key) != classes.end();
}

Value* Classes:: get(lets_str_t key){
	if(!is_exists(key)){
		throw ExecuteException(
			NS_Tools::string_format(ExceptionsError::E_UNKNOWN_CLASS, key.c_str())
		);
	}
	return classes[key];
}

void Classes::set(lets_str_t key, Value* cls){
	if(is_exists(key)){
		throw ExecuteException(
			NS_Tools::string_format(ExceptionsError::E_CNN_REWRITE_CLASS, key.c_str())
		);
	}
	classes[key] = cls;
}