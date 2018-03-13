//
//  lets/expressions/container_access_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/container_access_expr.hpp"
#include "../../include/expressions/variable_expr.hpp"
#include "../../include/lib/array_value.hpp"
#include "../../include/lib/string_value.hpp"
#include "../../include/lib/class_value.hpp"
#include "../../include/exception/execute.h"
#include "../../include/tools.hpp"

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
	try{
		return get();
	} catch(ExecuteException& e){
		e.row = indices.back()->get_position_row();
		e.col = indices.back()->get_position_col();
		throw e;
	}
}

Value *ContainerAccessExpression::get(){
	Value* container = get_container();
	Value* last = last_index();
	return container->get(last);
}

Value *ContainerAccessExpression::set(Value* value){
	Value* container = get_container();
	Value* last = last_index();
	container->set(last, value);
	return value;
}

Value* ContainerAccessExpression::get_container(){
	Value* container = root->eval();
	int last_i = (int)indices.size() - 1;
	for(int i = 0; i < last_i; ++i){
		Value* the_i = index(i);
		container = container->get(the_i);
	}
	return container;
}

Value* ContainerAccessExpression::last_index() {
	return index((int)indices.size() - 1);
}

lets_str_t ContainerAccessExpression::to_s(){
	return root->to_s() + "." + NS_Tools::vector_to_s<Expression *>(indices, ".");
}

ContainerAccessExpression::~ContainerAccessExpression(){}

Value* ContainerAccessExpression::index(int i){
	return indices[i]->eval();
}
