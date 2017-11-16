//
//  array_access_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_array_access_expr.hpp"
#include "../include/ex_execute.h"
#include "../include/l_variables.h"

ArrayAccessExpression::ArrayAccessExpression(lets_str_t variable, lets_vector_t<Expression*> indices):
	variable(std::move(variable)), indices(std::move(indices)){}

Value * ArrayAccessExpression::eval(){
	return get_array()->get(last_index());
}

lets_str_t ArrayAccessExpression::to_s(){ 
	// return variable + "[" + index->to_s() + "]";

	lets_str_t result = variable + "";

	for (Expression *index : indices){
		result += index->to_s();
		result +=  ", ";
	}

	result +=  "\b\b ";

	return result;
}

ArrayValue * ArrayAccessExpression::get_array(){
//	ArrayValue *array = consume_array(Variables::get(variable));
//    ArrayValue *array;
//	int last = (int)indices.size() - 1;
//	for (int i = 0; i < last; ++i){
//		array = consume_array(array->get(index(i)));
//	}
//	return array;
    return NULL;
}

int ArrayAccessExpression::last_index(){
	return index((int)indices.size() - 1);
}

int ArrayAccessExpression::index(int index){
	return (int)indices[index]->eval()->as_number();
}

ArrayValue *ArrayAccessExpression::consume_array(Value *value){
	if(Value *v = dynamic_cast<ArrayValue*>(value)){
		return dynamic_cast<ArrayValue*>(value);
	} else {
		throw ExecuteException("Array expected");
	}
}
