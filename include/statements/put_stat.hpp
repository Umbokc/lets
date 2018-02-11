//
//  include/statements/put_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_put_stat_hpp
#define include__s_put_stat_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"

class PutStatement : virtual public Statement{
public:
	Expression *expression;

	PutStatement(Expression *);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~PutStatement();
};


#endif /* include__s_put_stat_hpp */
