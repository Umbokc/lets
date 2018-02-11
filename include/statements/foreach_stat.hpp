//
//  include/statements/foreach_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_foreach_stat_hpp
#define include__s_foreach_stat_hpp

#include <string>
#include <vector>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"

class ForeachStatement : virtual public Statement{
public:
	lets_str_t key, val;
	Expression *container;
	Statement *body;

	ForeachStatement(lets_str_t,lets_str_t,Expression*,Statement*);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ForeachStatement();
};


#endif /* include__s_foreach_stat_hpp */
