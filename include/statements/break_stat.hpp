//
//  include/statements/break_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_break_stat_hpp
#define include__s_break_stat_hpp

#include <string>
#include "../main.h"
#include "../statement.h"

class BreakStatement : virtual public Statement{
public:

	BreakStatement();

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~BreakStatement();
};

#endif /* include__s_break_stat_hpp */
