//
//  include/statements/if_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_if_stat_hpp
#define include__s_if_stat_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"

class IfStatement : virtual public Statement{
public:

	Expression *expression;
	Statement *if_statement;
	Statement *else_statement;

	IfStatement(Expression*, Statement*, Statement*);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~IfStatement();
};

#endif /* include__s_if_stat_hpp */
