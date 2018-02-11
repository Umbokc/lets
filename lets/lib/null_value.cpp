//
//  lets/lib/null_value.cpp
//  lets
//
//  Created by Dragan Stepan on 27.01.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include "../../include/lib/null_value.hpp"
#include "../../include/lib/bool_value.hpp"
#include "../../include/lib/number_value.hpp"
#include "../../include/lib/string_value.hpp"
#include "../../include/lib/array_value.hpp"
#include "../../include/lib/map_value.hpp"

NullValue::NullValue(){}

bool NullValue::as_bool(){
	return false;
}

int NullValue::as_int(){
	return 0;
}

double NullValue::as_number(){
	return 0;
}

long NullValue::as_long(){
	return 0;
}

int NullValue::len(){
	return as_int();
}

Types NullValue::type(){
	return T_NULL;
}

lets_str_t NullValue::as_string(){
	return "";
}

lets_str_t NullValue::to_s(){
	return "null";
}

bool NullValue::equals(Value* obj) {
	if (this == obj) return true;
	// if (obj == NULL) return false;
	return false;
}

int NullValue::compareTo(Value *obj) {
	if (obj->type() == this->type())
		return true;
	return false;
}

NullValue::~NullValue(){}

NullValue *NullValue::THE_NULL = new NullValue();