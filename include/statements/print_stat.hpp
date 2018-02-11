//
//  include/statements/print_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_print_stat_hpp
#define include__s_print_stat_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../statement.h"

class PrintStatement : virtual public Statement{
public:
	Expression *expression;

	PrintStatement(Expression *expression);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~PrintStatement();
};


#endif /* include__s_print_stat_hpp */
