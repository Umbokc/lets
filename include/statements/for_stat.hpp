//
//  include/statements/for_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_for_stat_hpp
#define include__s_for_stat_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"

class ForStatement : virtual public Statement{
public:
	Statement *initialization;
	Expression *termination;
	Statement *increment;
	Statement *statement;

	ForStatement(Statement*,Expression*,Statement*,Statement*);
	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ForStatement();
};

#endif /* include__s_for_stat_hpp */
