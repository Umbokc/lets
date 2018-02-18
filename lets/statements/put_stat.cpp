//
//  lets/statements/put_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../../include/statements/put_stat.hpp"

PutStatement::PutStatement(Expression *expression):expression(std::move(expression)){}

void PutStatement::execute(){
	lets_simple_output(expression->eval()->to_s());
}

lets_str_t PutStatement::to_s(){
	return "put " + expression->to_s();
}

PutStatement::~PutStatement(){}
