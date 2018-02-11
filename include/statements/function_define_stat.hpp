//
//  include/statements/function_define_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__s_function_define_stat_hpp
#define include__s_function_define_stat_hpp

#include <string>
#include "../main.h"
#include "../arguments.hpp"
#include "../statement.h"

class FunctionDefineStatement : virtual public Statement{
public:
	lets_str_t name;
	Arguments args;
	Statement *body;

	FunctionDefineStatement(lets_str_t,Arguments,Statement*);

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~FunctionDefineStatement();
};

#endif /* include__s_function_define_stat_hpp */
