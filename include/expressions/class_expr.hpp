//
//  include/expressions/class_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 11.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__expressions__class_expr_hpp
#define include__expressions__class_expr_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"
#include "../lib/class_value.hpp"

class ClassExpression : virtual public Expression, virtual public Statement{
public:
	Expression *class_expr;
	lets_vector_t<Expression *> arguments;

	ClassExpression();
	~ClassExpression();
	ClassExpression(Expression*);

	void add_arguments(Expression*);

	void execute();
	Value *eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t name_to_s();
	lets_str_t args_to_s();

	lets_str_t to_s();
private:
	Value* consume_class(Expression*);
	Value* get_class(lets_str_t);
};

#endif /* include__expressions__class_expr_hpp */

