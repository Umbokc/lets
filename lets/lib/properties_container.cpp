//
//  lets/lib/properties_container.cpp
//  lets
//
//  Created by Dragan Stepan on 21.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include "../../include/lib/null_value.hpp"
#include "../../include/lib/properties_container.hpp"

PropertiesContainer::PropertiesContainer(){}

bool PropertiesContainer::is_exists(const lets_str_t& name){
	return data.find(name) != data.end();
}

bool PropertiesContainer::is_constant(const lets_str_t& name){
	if (this->is_exists(name))
		return data.at(name).is_constant;
	else
		return false;
}

Value* PropertiesContainer::get(const lets_str_t& name){
	if (this->is_exists(name))
		return data.at(name).value;
	return NullValue::THE_NULL;
}

void PropertiesContainer::set(const lets_str_t& name, Value* val){
	data[name] = Property(val);
}

void PropertiesContainer::set(const lets_str_t& name, Property var){
	data[name] = var;
}

void PropertiesContainer::remove(const lets_str_t& name){
	data.erase(name);
}

size_t PropertiesContainer:: size(){
	return data.size();
}

lets_str_t PropertiesContainer::to_s(){
	return "PropertiesContainer";
}

PropertiesContainer::~PropertiesContainer(){}
