//
//  s_return_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_return_stat_hpp
#define s_return_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class ReturnStatement : virtual public Statement{
public:
	Value *result;
	Expression *expression;

	ReturnStatement(Expression *);

	Value *get_result();

	void execute();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~ReturnStatement();
};


#endif /* s_return_stat_hpp */
