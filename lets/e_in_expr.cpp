//
//  lets/e_in_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 08.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_in_expr.hpp"
#include "../include/l_array_value.hpp"
#include "../include/l_map_value.hpp"
#include "../include/l_string_value.hpp"
#include "../include/l_number_value.hpp"

InExpression::InExpression(Expression* e, Expression* c):expression(std::move(e)), container(std::move(c)){}

Value* InExpression::eval(){

	bool result;

	Value* val = expression->eval();
	Value* object = container->eval();

	if(ArrayValue *array_val = dynamic_cast<ArrayValue*>(object)){

		result = (array_val->has(val));

	// } else if(MapValue *map_val = dynamic_cast<MapValue*>(object)){

		// result = (map_val->has(val->to_s()));
		// result = false;

	} else if(StringValue *string_val = dynamic_cast<StringValue*>(object)){

		result = (string_val->has(val));

	}

	return result ? NumberValue::ONE : NumberValue::ZERO;
}

lets_str_t InExpression::to_s(){
	return expression->to_s() + " in " + container->to_s();
}

InExpression::~InExpression(){}
