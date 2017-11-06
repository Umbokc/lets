//
//  s_do_while_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_do_while_stat.hpp"
#include "../include/s_break_stat.hpp"
#include "../include/s_continue_stat.hpp"

DoWhileStatement::DoWhileStatement(Expression *condition,Statement *statement):
    condition(std::move(condition)), statement(std::move(statement)){}

void DoWhileStatement::execute(){
    do {
        try{
            statement->execute();
        } catch (BreakStatement *bs){
            break;
        } catch (ContinueStatement *cs){
            // continue;
        }
    }
    while(condition->eval()->as_number() != 0);
}

lets_str_t DoWhileStatement::to_s(){
    
    lets_str_t result = "do " +
    statement->to_s() +
    " while " +
    condition->to_s();
    
    return result;
}

DoWhileStatement::~DoWhileStatement(){
    // delete[] condition;
    // delete[] statement;
}
