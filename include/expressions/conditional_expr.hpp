//
//  include/e_conditional_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_conditional_expr_hpp
#define include__e_conditional_expr_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "binary_expr.hpp"

class ConditionalExpression : virtual public Expression{
public:
	typedef enum {EQUALS, NOT_EQUALS, LT, LTEQ, GT, GTEQ, AND, OR } Operator;
	static const lets_str_t OperatorString[8];

	ConditionalExpression::Operator operation;
	Expression *expr1;
	Expression *expr2;

	ConditionalExpression(ConditionalExpression::Operator, Expression*, Expression*);

	Value* eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ConditionalExpression();
};

#endif /* include__e_conditional_expr_hpp */
