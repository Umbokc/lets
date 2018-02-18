//
//  lets/expressions/array_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/array_expr.hpp"
#include "../../include/lib/array_value.hpp"
#include "../../include/tools.hpp"

ArrayExpression::ArrayExpression(lets_vector_t<Expression *> elems)
	:elements(std::move(elems)){}

Value *ArrayExpression::eval(){

	int size = (int)elements.size();
	ArrayValue *array = new ArrayValue(size);

	for (int i = 0; i < size; i++) {
		array->set(i, elements[i]->eval());
	}

	return array;
}

lets_str_t ArrayExpression::to_s(){
	return "[ " + NS_Tools::vector_to_s<Expression*>(elements, ", ") + " ]";
}

ArrayExpression::~ArrayExpression(){}
