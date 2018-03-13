//
//  lets/statements/block_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../../include/statements/block_stat.hpp"
#include "../../include/exception/execute.h"

BlockStatement::BlockStatement(){}

void BlockStatement::add(Statement *statement){
	statements.push_back(statement);
}

void BlockStatement::execute(){
	LETS_TRY_EXCEPTION_EXECUTE_START()
	for(auto st : statements){
		st->execute();
	}
	LETS_TRY_EXCEPTION_EXECUTE_END()
}

lets_str_t BlockStatement::to_s(){
	lets_str_t result = "";

	for(auto st : statements){
		result += st->to_s();
		result.push_back('\n');
	}

	return result;
}

BlockStatement::~BlockStatement(){}
