//
//  s_include_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 20.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_include_stat_hpp
#define s_include_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class IncludeStatement : virtual public Statement, virtual public Expression{
public:

	Expression *expression;

	IncludeStatement(Expression*);

	void execute();
	Value* eval();

	Statement* load_program(const lets_str_t&);

	lets_str_t to_s();

	~IncludeStatement();
};

#endif /* s_include_stat_hpp */
