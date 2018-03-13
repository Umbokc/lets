//
//  include/expressions/variable_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_variable_expr_hpp
#define include__e_variable_expr_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"
#include "../accessible.h"

class VariableExpression : virtual public Expression, virtual public Accessible{
public:

	mutable lets_str_t name;

	VariableExpression(lets_str_t);

	Value* eval();
	Value* get();
	Value* set(Value*);

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~VariableExpression();
};

#endif /* include__e_variable_expr_hpp */
