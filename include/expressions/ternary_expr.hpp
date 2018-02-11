//
//  include/e_ternary_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_ternary_expr_hpp
#define include__e_ternary_expr_hpp

#include <string>
#include <map>
#include "../main.h"
#include "../expression.h"

class TernaryExpression : virtual public Expression{
public:
	Expression *condition;
	Expression *trueExpr, *falseExpr;


	TernaryExpression(Expression*,Expression*,Expression*);

	Value* eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~TernaryExpression();
};

#endif /* include__e_ternary_expr_hpp */
