//
//  lets/statements/continue_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/statements/continue_stat.hpp"

ContinueStatement::ContinueStatement(){
}

void ContinueStatement::execute(){
	throw this;
}
lets_str_t ContinueStatement::to_s(){
	return "continue";
}

ContinueStatement::~ContinueStatement(){}
