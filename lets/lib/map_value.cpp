//
//  lets/lib/map_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg

#include "../../include/lib/include_values.h"
#include "../../include/exception/execute.h"

MapValue::MapValue(){this->construct();}

MapValue::MapValue(lets_map_t<lets_str_t, Value *>& elems){
		this->elems.swap(elems);
		this->construct();
}

MapValue::MapValue(MapValue *map_val){
		new MapValue(map_val->elems);
		this->construct();
}

Value* MapValue::construct(){
	this->set_class_name("Map");
	DEFAULT_METHODS_OF_CLASS()
}

Value* MapValue::construct(FUNCS_ARGS args){

	if(args.size() != 0){
		uint size = args.size();
		for (int i = 0; i < size; ++i){
			if(args.at(i)->type() == T_ARRAY){
				ArrayValue* arr = dynamic_cast<ArrayValue*>(args.at(i));
				if(arr->size() == 2){
					this->set(arr->get(0), arr->get(1));
				}
			}
		}
	}

	return this;
}

ArrayValue* MapValue::to_pairs(){
	int size = this->elems.size();
	ArrayValue* result = new ArrayValue(size);
	lets_vector_t<Value*> elem;
	for(auto entry: this->elems){
		result->add(new ArrayValue({new StringValue(entry.first), entry.second}));
	}
}

bool MapValue::is_exists(Value *key){
	return this->has(key->to_s());
}

Value *MapValue::get(lets_str_t key){
	if(this->has(key))
		return this->elems[key];

	return NullValue::THE_NULL;
}

Value *MapValue::get(Value *key){
	if(this->is_exists(key))
		return this->get(key->to_s());

	return this->get_prop(key);

}

Value *MapValue::get_by_index(size_t index){
	if(index < this->elems.size()){
		auto it = this->elems.begin();
		std::advance(it, index);
		return new ArrayValue({new StringValue((*it).first), (*it).second});
	}
	return NullValue::THE_NULL;
}

lets_map_t<lets_str_t, Value *> MapValue::get_all(){
	return this->elems;
}

bool MapValue::has(lets_str_t key){
	return this->elems.find(key) != elems.end();
}

bool MapValue::has(lets_str_t key, Value *value){
	if (this == value) return false;
	if (!has(key)) return false;
	return this->elems[key]->equals(value);
}

void MapValue::set(Value *key, Value *value){
	this->elems[key->as_string()] = value;
}

void MapValue::set(Value *key, Function *function){
	this->elems[key->as_string()] = new FunctionValue(function);
}

bool MapValue::as_bool(){
	return this->elems.size() != 0;
}

int MapValue::as_int(){
	return (int) as_number();
}

double MapValue::as_number(){
	throw ExecuteException("Cannot cast map to number");
}

long MapValue::as_long(){
	return (long)as_number();
}

int MapValue::len(){
	return (int)this->elems.size();
}

lets_str_t MapValue::as_string(){
	lets_str_t result = "{";

	int i = 0;
	int size = this->len();
	for (auto& elem : this->elems){
		result += elem.first;
		result +=  " : ";
		result += elem.second->to_s();
		if(i != size-1) result +=  ", ";
		i++;
	}
	result +=  "}";

	return result;
}

lets_str_t MapValue::to_s(){
	return as_string();
}

Types MapValue::type(){
	return Types::T_MAP;
}

bool MapValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;
	MapValue* the_obj;
	if ((the_obj = dynamic_cast<MapValue*>(obj)) == NULL) return false;
	if (the_obj->len() != this->len()) return false;

	for (auto& elem : the_obj->elems){
		if(!this->has(elem.first, elem.second)){
			return false;
		}
	}	

	return true;
}

int MapValue::compareTo(Value *obj){
	if (obj->type() == this->type()) {
		int length_compare = lets_compare(len(), dynamic_cast<MapValue*>(obj)->len());
		if (length_compare != 0) return length_compare;
	}
	return lets_compare(as_string(), obj->as_string());
}

MapValue::~MapValue(){}

MapValue *NS_MapValue::add(MapValue *arr, Value *key, Value *value){
	lets_map_t<lets_str_t, Value *> result = arr->get_all();
	result[key->to_s()] = value;
	return new MapValue(result);
}

MapValue *NS_MapValue::merge(MapValue *value1, MapValue *value2){
	lets_map_t<lets_str_t, Value *> arr1 = value1->get_all(),
	arr2 = value2->get_all();

	lets_map_t<lets_str_t, Value *> result;

	for(auto& elem : arr1){ result[elem.first] = elem.second; }
	for(auto& elem : arr2){ result[elem.first] = elem.second; }

	arr1.clear();
	arr2.clear();

	return new MapValue(result);
}
