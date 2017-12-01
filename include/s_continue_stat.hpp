//
//  s_continue_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_continue_stat_h
#define s_continue_stat_h

#include <string>
#include "main.h"
#include "statement.h"

class ContinueStatement : virtual public Statement{
public:

	ContinueStatement();

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ContinueStatement();
};

#endif /* s_continue_stat_h */
