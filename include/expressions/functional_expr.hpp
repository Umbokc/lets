//
//  include/e_functional_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_functional_expr_hpp
#define include__e_functional_expr_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"
#include "../lib/map_value.hpp"

class FunctionalExpression : virtual public Expression, virtual public Statement{
public:
	lets_str_t function_name;
	Expression* function_expr;
	lets_vector_t<Expression *> arguments;

	FunctionalExpression();
	~FunctionalExpression();
	FunctionalExpression(Expression* function_expr);

	void add_arguments(Expression*);

	void execute();
	Value *eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t name_to_s();
	lets_str_t args_to_s();

	lets_str_t to_s();
private:
	Function* consume_function(Expression*);
	Function* get_function(lets_str_t);
};

#endif /* include__e_functional_expr_hpp */
