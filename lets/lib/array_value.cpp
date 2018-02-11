//
//  lets/lib/array_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg

#include "../../include/lib/array_value.hpp"
#include "../../include/lib/number_value.hpp"
#include "../../include/lib/null_value.hpp"
#include "../../include/exception/execute.h"
#include "../../include/tools.hpp"


ArrayValue::ArrayValue(int size){
	elements.resize(size);
}

ArrayValue::ArrayValue(Value *val){
	this->elements.push_back(val);
}

ArrayValue::ArrayValue(lets_vector_t<Value *> elements){
	this->elements.swap(elements);
}

ArrayValue::ArrayValue(ArrayValue *array){
	new ArrayValue(array->elements);
}

void ArrayValue::add(Value *val){
	this->elements.push_back(val);
}

void ArrayValue::add_forward(Value *val){
	this->elements.insert(this->elements.begin(), val);
}

Value *ArrayValue::get(int index){

	if(index >= 0 && index < this->len())
		return this->elements[index];

	throw ExecuteException("Undefined index of array");
}

Value *ArrayValue::get_always(int index){

	if(index >= 0 && index < this->len())
		return this->elements[index];

	return NullValue::THE_NULL;
}

lets_vector_t<Value *> ArrayValue::get_all(){
	return this->elements;
}

bool ArrayValue::has(Value *value){
	if (this == value) return false;

	uint size = this->elements.size();

	for (uint i = 0; i < size; ++i){
		if(this->elements.at(i)->equals(value)){
			return true;
		}
	}

	return false;
}

bool ArrayValue::has(Value *value, int index){
	if (this == value) return false;
	if (index < 0) return false;

	uint size = this->elements.size();

	for (uint i = 0; i < size; ++i){
		if(this->elements.at(i)->equals(value) && index == i){
			return true;
		}
	}

	return false;
}

void ArrayValue::set(int index, Value *value){

	if(index > -1 && index < this->len()){
		this->elements[index] = value;
		return;
	}

	throw ExecuteException("Undefined index "+ to_str(index) +" of array");
}

bool ArrayValue::as_bool(){
	return this->elements.size() != 0;
}

int ArrayValue::as_int(){
	return (int) as_number();
}

double ArrayValue::as_number(){
	throw ExecuteException("Cannot cast array to number");
}

long ArrayValue::as_long(){
	return (long) as_number();
}

int ArrayValue::len(){
	return size();
}

int ArrayValue::size(){
	return (int)this->elements.size();
}

lets_str_t ArrayValue::as_string(){
	return "[ " + NS_Tools::vector_to_s<Value *>(elements, ", ") + " ]";
}

lets_str_t ArrayValue::to_s(){
	return as_string();
}

Types ArrayValue::type(){
	return Types::T_ARRAY;
}

bool ArrayValue::equals(Value* obj) {
	if (this == obj) return true;
	if (obj == NULL) return false;
	if (!dynamic_cast<ArrayValue*>(obj)) return false;
	return std::equal(
		this->elements.begin(),
		this->elements.end(),
		dynamic_cast<ArrayValue*>(obj)->elements.begin()
	);
}

int ArrayValue::compareTo(Value *obj){
	if (obj->type() == this->type()) {
		int length_compare = lets_compare(len(), dynamic_cast<ArrayValue*>(obj)->len());
		if (length_compare != 0) return length_compare;
	}
	return lets_compare(as_string(), obj->as_string());
}

ArrayValue::~ArrayValue(){}

namespace NS_ArrayValue{
	ArrayValue *add(ArrayValue *arr, Value *value){
		lets_vector_t<Value *> result = arr->get_all();
		result.push_back(value);
		return new ArrayValue(result);
	}

	ArrayValue *add_forward(ArrayValue *arr, Value *value){
		lets_vector_t<Value *> result = arr->get_all();
		result.insert(result.begin(), value);
		return new ArrayValue(result);
	}

	ArrayValue *merge(ArrayValue *value1, ArrayValue *value2) {
		lets_vector_t<Value *> arr1 = value1->get_all(),
		arr2 = value2->get_all();

		lets_vector_t<Value *> result;

		result.reserve(arr1.size() + arr2.size());
		result.insert(result.end(), arr1.begin(), arr1.end());
		result.insert(result.end(), arr2.begin(), arr2.end());

		arr1.clear();
		arr2.clear();

		return new ArrayValue(result);
	}
}
