//
//  include/statements/use_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_use_stat_hpp
#define include__s_use_stat_hpp

#include <string>
#include "../main.h"
#include "../expressions/array_expr.hpp"
#include "../statement.h"

class UseStatement : virtual public Statement{
public:

	Expression *expression;
	Expression *elements;

	UseStatement(Expression*);
	UseStatement(Expression*, Expression*);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~UseStatement();
};

#endif /* include__s_use_stat_hpp */
