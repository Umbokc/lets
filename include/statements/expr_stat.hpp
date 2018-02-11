//
//  include/statements/expr_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_expr_stat_hpp
#define include__s_expr_stat_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"

class ExprStatement : virtual public Expression, virtual public Statement{
public:
	Expression *expr;

	ExprStatement(Expression*);

	void execute();

	Value *eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ExprStatement();
};

#endif /* include__s_expr_stat_hpp */
