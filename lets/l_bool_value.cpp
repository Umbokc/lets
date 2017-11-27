//
//  lets/l_bool_value.cpp
//  lets
//
//  Created by Dragan Stepan on 27.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/l_bool_value.hpp"
#include "../include/l_number_value.hpp"
#include "../include/l_string_value.hpp"
#include "../include/l_array_value.hpp"
#include "../include/l_map_value.hpp"

BoolValue::BoolValue(bool value){
	this->value = value;
}

BoolValue::BoolValue(NumberValue* val){ this->value = val->as_bool(); }
BoolValue::BoolValue(StringValue* val){ this->value = val->as_bool(); }
BoolValue::BoolValue(ArrayValue* val){ this->value = val->as_bool(); }
BoolValue::BoolValue(MapValue* val){ this->value = val->as_bool(); }

bool BoolValue::as_bool(){
	return this->value;
}

int BoolValue::as_int(){
	return (int)as_number();
}

double BoolValue::as_number(){
	return (double)this->value;
}

long BoolValue::as_long(){
	return (long)this->value;
}

int BoolValue::len(){
	return as_int();
}

Types BoolValue::type(){
	return T_BOOL;
}

lets_str_t BoolValue::as_string(){
	return this->value ? "true" : "false";
}

lets_str_t BoolValue::to_s(){
	return as_string();
}

bool BoolValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;

	bool other = dynamic_cast<BoolValue*>(obj)->value;
	return (this->value == other);
}

int BoolValue::compareTo(Value *obj) {
	if (obj->type() == this->type()) {
		bool other = dynamic_cast<BoolValue*>(obj)->value;
		return lets_compare(this->value, other);
	}

	return lets_compare(as_string(), obj->as_string());
}

BoolValue::~BoolValue(){}

BoolValue* BoolValue::TRUE = new BoolValue(true);
BoolValue* BoolValue::FALSE = new BoolValue(false);
