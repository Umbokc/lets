//
//  e_container_access_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_container_access_expr.hpp"
#include "../include/e_variable_expr.hpp"
#include "../include/l_array_value.hpp"
#include "../include/l_string_value.hpp"
#include "../include/ex_execute.h"
#include "../include/tools.hpp"

ContainerAccessExpression::ContainerAccessExpression(){}

ContainerAccessExpression::ContainerAccessExpression(lets_str_t variable, lets_vector_t<Expression*> indices) {
	this->root = new VariableExpression(variable),
	this->indices = indices;
}

ContainerAccessExpression::ContainerAccessExpression(Expression* root, lets_vector_t<Expression*> indices) :
root(std::move(root)), indices(std::move(indices)){
	root_is_var = (dynamic_cast<VariableExpression*>(this->root)) ? true : false;
}

bool ContainerAccessExpression::root_is_variable(){
	return root_is_var;
}

Expression *ContainerAccessExpression::get_root(){
	return root;
}

Value *ContainerAccessExpression::eval(){
	return get();
}

Value *ContainerAccessExpression::get(){
	Value* container = get_container();
	Value* last = last_index();
	switch(container->type()){
		case Types::T_ARRAY:
		return dynamic_cast<ArrayValue*>(container)->get(last->as_int());
		case Types::T_STRING:
		return new StringValue(
			dynamic_cast<StringValue*>(container)->get_c(last->as_int())
			);
		case Types::T_MAP:
		return dynamic_cast<MapValue*>(container)->get(last);
		default:
		throw ExecuteException(
			"Array or map expected. Got " + TypesString[container->type()]
			);
	}
}

Value *ContainerAccessExpression::set(Value* value){
	Value* container = get_container();
	Value* last = last_index();
	switch(container->type()){
		case Types::T_ARRAY:
		dynamic_cast<ArrayValue*>(container)->set(last->as_int(), value);
		return value;
		case Types::T_MAP:
		dynamic_cast<MapValue*>(container)->set(last, value);
		return value;
		default:
		throw ExecuteException(
			"Array or map expected. Got " + TypesString[container->type()]
			);
	}
}

Value* ContainerAccessExpression::get_container(){
	Value* container = root->eval();
	int last_i = (int)indices.size() - 1;
	for(int i = 0; i < last_i; ++i){
		Value* the_i = index(i);
		switch(container->type()){
			case Types::T_ARRAY :{
				int array_index = the_i->as_int();
				container = dynamic_cast<ArrayValue*> (container)->get(array_index);
				break;
			}
			case Types::T_MAP :{
				container = dynamic_cast<MapValue*> (container)->get(the_i);
				break;
			}
			default:
			throw ExecuteException("Array or map expected");
		}
	}
	return container;
}

Value* ContainerAccessExpression::last_index() {
	return index((int)indices.size() - 1);
}

MapValue* ContainerAccessExpression::consume_map(Value* value){
	if(value->type() != Types::T_MAP){
		throw ExecuteException("Map expected");
	}
	return dynamic_cast<MapValue*>(value);
}

lets_str_t ContainerAccessExpression::to_s(){
	return root->to_s() + NS_Tools::vector_to_s<Expression *>(indices, ".");
}

ContainerAccessExpression::~ContainerAccessExpression(){}

Value* ContainerAccessExpression::index(int i){
	return indices[i]->eval();
}
