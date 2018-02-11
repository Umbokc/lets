//
//  lets/statements/while_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/statements/while_stat.hpp"
#include "../../include/statements/break_stat.hpp"
#include "../../include/statements/continue_stat.hpp"

WhileStatement::WhileStatement(Expression *condition,Statement *statement):
	condition(std::move(condition)), statement(std::move(statement)){}

void WhileStatement::execute(){
	while(condition->eval()->as_number() != 0){
		try{
			statement->execute();
		} catch (BreakStatement *bs){
			break;
		} catch (ContinueStatement *cs){
			// continue;
		}
	}
}

lets_str_t WhileStatement::to_s(){
	lets_str_t result = "while " +
	condition->to_s() + " " + statement->to_s();
	return result;
}

WhileStatement::~WhileStatement(){}
