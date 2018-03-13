//
//  lets/lib/array_value.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg

#include "../../include/lib/include_values.h"
#include "../../include/exception/error.h"
#include "../../include/exception/execute.h"
#include "../../include/tools.hpp"

#define UPDATE_SIZE() this->define_prop("size", Property(new NumberValue(this->size()), false, true));

ArrayValue::ArrayValue(){
	this->construct();
}

ArrayValue::ArrayValue(int size){
	elements.resize(size);
	this->construct();
}

ArrayValue::ArrayValue(Value *val){
	this->elements.push_back(val);
	this->construct();
}

ArrayValue::ArrayValue(lets_vector_t<Value *> elements){
	this->elements.swap(elements);
	this->construct();
}

ArrayValue::ArrayValue(ArrayValue *array){
	this->elements = array->elements;
	this->construct();
}

Value* ArrayValue::construct(){
	this->set_class_name("Array");
	UPDATE_SIZE();

	DEFAULT_METHODS_OF_CLASS()

	ADD_METHOD_TO_CLASS(Array, "join", Join, {
		return new StringValue(
			NS_Tools::vector_to_s<Value *>(
				self->elements,
				((args.size() == 1) ? args.at(0)->as_string() : ",")
			)
		);
	}, "")

	ADD_METHOD_TO_CLASS(Array, "reverse", Reverse, {
		std::reverse(std::begin(self->elements), std::end(self->elements));
		return self;
	}, "")

	ADD_METHOD_TO_CLASS(Array, "is_empty", Is_empty, {
		return self->elements.empty() ? BoolValue::TRUE : BoolValue::FALSE;
	}, "")

	ADD_METHOD_TO_CLASS(Array, "has", Has, {
		if(args.size() == 0) throw ExecuteException("Method "+self->get_class_name()+".has(arg*, pos = null) one args expected");
		if(args.size() == 2){
			return self->has(args.at(0), args.at(1)->as_int()) ? BoolValue::TRUE : BoolValue::FALSE;
		}
		return self->has(args.at(0)) ? BoolValue::TRUE : BoolValue::FALSE;
	}, "arg*, pos = null")

	ADD_METHOD_TO_CLASS(Array, "get", Get, {
		if(args.size() == 0) throw ExecuteException("Method "+self->get_class_name()+".get(arg*) one args expected");
		return self->get(args.at(0)->as_int());
	}, "arg*, pos = null")

	ADD_METHOD_TO_CLASS(Array, "push", Push, {
		if(args.size() == 0) throw ExecuteException("Method "+self->get_class_name()+".push(arg*) one args expected");
		self->add(args.at(0));
		return args.at(0);
	}, "arg*")

	ADD_METHOD_TO_CLASS(Array, "count", Count, {
		if(args.size() == 0) throw ExecuteException("Method "+self->get_class_name()+".count(arg*) one args expected");
		return new NumberValue((int)self->count(args.at(0)));
	}, "arg*")

	return this;
}

Value* ArrayValue::construct(FUNCS_ARGS args){
	if(args.size() == 0){
		elements.resize(0);
	} else if(args.size() == 1){
		this->elements = create_array(NullValue::THE_NULL, args, 0)->elements;
	} else {
		this->elements = create_array(args.at(0), args, 1)->elements;
	}

	UPDATE_SIZE();

	return this;
}

ArrayValue* ArrayValue::create_array(Value* def, FUNCS_ARGS args, int index){

	int size = args[index]->as_int();
	int last = (int)args.size() -1;

	ArrayValue *array = new ArrayValue(size);

	if(index == last){
		for (int i = 0; i < size; ++i){
			array->set(i, def);
		}
	} else if(index < last) {
		for (int i = 0; i < size; ++i){
			array->set(i, create_array(def, args, index+1));
		}
	}

	return array;
}

void ArrayValue::add(Value *val){
	this->elements.push_back(val);
	UPDATE_SIZE();
}

void ArrayValue::add_forward(Value *val){
	this->elements.insert(this->elements.begin(), val);
	UPDATE_SIZE();
}

Value *ArrayValue::get(int index){

	if(index >= 0 && index < this->len())
		return this->elements[index];

	throw ExecuteException("Undefined index "+ to_str(index) +" of array");
}

Value *ArrayValue::get_always(int index){

	if(index >= 0 && index < this->len())
		return this->elements[index];

	return NullValue::THE_NULL;
}

lets_vector_t<Value *> ArrayValue::get_all(){
	return this->elements;
}

size_t ArrayValue::count(Value *value){

	lets_vector_t<Value*>::iterator first = this->elements.begin();
	lets_vector_t<Value*>::iterator last = this->elements.end();
	size_t res = 0;

	while (first!=last) {
		if((*first)->equals(value)) res++;
		++first;
	}

	return res;
}

bool ArrayValue::has(Value *value){
	if (this == value) return false;

	if(this->count(value) == 0)
		return false;

	return true;
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
	return this->elements.size() != 20;
}

int ArrayValue::as_int(){
	return (int) as_number();
}

double ArrayValue::as_number(){
	throw ExecuteException(ExceptionsError::E_CNN_ARR_TO_NUM);
}

long ArrayValue::as_long(){
	return (long) as_number();
}

int ArrayValue::len(){
	return this->size();
}

int ArrayValue::size(){
	return (int)this->elements.size();
}

Value* ArrayValue::get(Value* key){
	if(key->type() == Types::T_NUMBER)
		return this->get(key->as_int());
	else
		return this->get_prop(key);
}

void ArrayValue::set(Value* key, Value* value){
	if(key->type() == Types::T_NUMBER)
		this->set(key->as_int(), value);
	else
		this->set_prop(key, value);
}

lets_str_t ArrayValue::as_string(){
	return "[" + NS_Tools::vector_to_s<Value *>(elements, ", ") + "]";
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
	ArrayValue* the_obj;
	if ((the_obj = dynamic_cast<ArrayValue*>(obj)) == NULL) return false;
	if (the_obj->size() != this->size()) return false;


	uint size = this->elements.size();

	for (uint i = 0; i < size; ++i){
		if(!this->elements.at(i)->equals(the_obj->elements.at(i))){
			return false;
		}
	}

	return true;
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
