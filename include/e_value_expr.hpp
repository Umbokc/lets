//
//  e_value_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__expr__value_expr_hpp
#define ast__expr__value_expr_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "l_function.h"
#include "l_number.hpp"

class ValueExpression : virtual public Expression {
public:
	Value *value;

	ValueExpression();

	ValueExpression(int);
	ValueExpression(double);
	ValueExpression(long);
	ValueExpression(Number);

	ValueExpression(lets_str_t);
	ValueExpression(Function*);
	ValueExpression(Value*);

	Value *eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ValueExpression();
};

#endif /* ast__expr__value_expr_hpp */
