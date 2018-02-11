//
//  lets/statements/print_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../../include/statements/print_stat.hpp"

PrintStatement::PrintStatement(Expression *expression):expression(std::move(expression)){}

void PrintStatement::execute(){
	std::cout << expression->eval()->to_s() << std::endl;
}

lets_str_t PrintStatement::to_s(){
	return "print " + expression->to_s() + "\n";
}

PrintStatement::~PrintStatement(){}