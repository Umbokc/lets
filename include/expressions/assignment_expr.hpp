//
//  include/expressions/assignment_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_assignment_expr_hpp
#define include__e_assignment_expr_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"
#include "../accessible.h"
#include "../lib/function.h"

#include "binary_expr.hpp"

class AssignmentExpression : virtual public Expression, virtual public Statement{
public:
	NS_Binary::Operator operation;
	Accessible *target;
	Expression *expression;

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	AssignmentExpression(NS_Binary::Operator, Accessible*, Expression*);
	void execute();
	Value* eval();
	lets_str_t to_s();
	~AssignmentExpression();
};

#endif /* include__e_assignment_expr_hpp */
