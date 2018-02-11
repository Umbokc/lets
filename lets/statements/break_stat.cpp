//
//  lets/statements/break_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/statements/break_stat.hpp"

BreakStatement::BreakStatement(){
}

void BreakStatement::execute(){
	throw this;
}

lets_str_t BreakStatement::to_s(){
	return "break";
}

BreakStatement::~BreakStatement(){}
