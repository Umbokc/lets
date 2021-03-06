//
//  lets/expressions/in_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 08.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/in_expr.hpp"
#include "../../include/lib/array_value.hpp"
#include "../../include/lib/map_value.hpp"
#include "../../include/lib/string_value.hpp"
#include "../../include/lib/bool_value.hpp"

InExpression::InExpression(lets_vector_t<Expression*> e, Expression* c):expressions(std::move(e)), container(std::move(c)){}

Value* InExpression::eval(){
	LETS_TRY_EXCEPTION_EXECUTE_START()
	bool result = false;

	Value* val = expressions.at(0)->eval();
	Value* object = container->eval();

	if (expressions.size() == 2) {
		Value* val2 = expressions.at(1)->eval();
		if(ArrayValue *array_val = dynamic_cast<ArrayValue*>(object)){
			result = (array_val->has(val, val2->as_int()));
		} else if(MapValue *map_val = dynamic_cast<MapValue*>(object)){
			result = (map_val->has(val->to_s(), val2));
		} else if(StringValue *string_val = dynamic_cast<StringValue*>(object)){
			result = (string_val->has(val, val2->as_int()));
		}
	} else {
		if(ArrayValue *array_val = dynamic_cast<ArrayValue*>(object)){
			result = (array_val->has(val));
		} else if(MapValue *map_val = dynamic_cast<MapValue*>(object)){
			result = (map_val->has(val->to_s()));
		} else if(StringValue *string_val = dynamic_cast<StringValue*>(object)){
			result = (string_val->has(val));
		}
	}

	return result ? BoolValue::TRUE : BoolValue::FALSE;
	LETS_TRY_EXCEPTION_EXECUTE_END()
}

lets_str_t InExpression::to_s(){
	if (expressions.size() == 2)
		return expressions.at(0)->to_s() + ", " + expressions.at(1)->to_s() + " in " + container->to_s();
	else
		return expressions.at(0)->to_s() + " in " + container->to_s();
}

InExpression::~InExpression(){}
