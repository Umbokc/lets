//
//  include/expressions/array_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_array_expr_hpp
#define include__e_array_expr_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"

class ArrayExpression : virtual public Expression{
public:
	lets_vector_t<Expression *> elements;

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	ArrayExpression(lets_vector_t<Expression *> elements);
	Value *eval();
	lets_str_t to_s();
	~ArrayExpression();
};


#endif /* include__e_array_expr_hpp */
