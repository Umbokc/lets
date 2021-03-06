//
//  include/expressions/map_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_map_expr_hpp
#define include__e_map_expr_hpp

#include <string>
#include <map>
#include "../main.h"
#include "../expression.h"
#include "../lib/map_value.hpp"

class MapExpression : virtual public Expression{
public:
	lets_map_t<Expression*, Expression*> elements;

	MapExpression(lets_map_t<Expression*, Expression*>);

	Value *eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~MapExpression();
};


#endif /* include__e_map_expr_hpp */
