//
//  lets/statements/print_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../../include/statements/print_stat.hpp"
#include "../../include/lib/number_value.hpp"

PrintStatement::PrintStatement(Expression *expression):expression(std::move(expression)){}

void PrintStatement::execute(){
	LETS_TRY_EXCEPTION_EXECUTE_START()
	lets_output(expression->eval()->to_s());
	LETS_TRY_EXCEPTION_EXECUTE_END()
}

lets_str_t PrintStatement::to_s(){
	return "print " + expression->to_s() + "";
}

PrintStatement::~PrintStatement(){}
