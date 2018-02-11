//
//  include/e_array_access_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_array_access_expr_hpp
#define include__e_array_access_expr_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"
#include "../lib/array_value.hpp"

class ArrayAccessExpression : virtual public Expression{
public:
	lets_str_t variable;
	lets_vector_t<Expression*> indices;

	ArrayAccessExpression(lets_str_t, lets_vector_t<Expression*>);

	Value * eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();
	ArrayValue * get_array();
	int last_index();

private:
	int index(int index);
	ArrayValue *consume_array(Value *value);
};

#endif /* include__e_array_access_expr_hpp */
