//
//  e_container_access_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef e_container_access_expr_hpp
#define e_container_access_expr_hpp

#include <string>
#include <vector>
#include "main.h"
#include "expression.h"
#include "accessible.h"
#include "l_map_value.hpp"

class ContainerAccessExpression : virtual public Expression, virtual public Accessible {
private:
	bool root_is_var;
public:
	Expression* root;
	lets_vector_t<Expression*> indices;

	ContainerAccessExpression();
	ContainerAccessExpression(lets_str_t, lets_vector_t<Expression*>);
	ContainerAccessExpression(Expression*, lets_vector_t<Expression*>);

	bool root_is_variable();

	Expression *get_root();

	Value *eval();
	Value *get();
	Value *set(Value* value);

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	Value* get_container();
	Value* last_index();
	MapValue* consume_map(Value* value);

	lets_str_t to_s();

	~ContainerAccessExpression();
private:
	Value* index(int i);
};

#endif /* e_container_access_expr_hpp */
