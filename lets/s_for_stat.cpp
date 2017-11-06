//
//  s_for_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_for_stat.hpp"
#include "../include/s_break_stat.hpp"
#include "../include/s_continue_stat.hpp"

ForStatement::ForStatement(Statement *initialization, Expression *termination, Statement *increment, Statement *statement):
    initialization(std::move(initialization)),
    termination(std::move(termination)),
    increment(std::move(increment)),
    statement(std::move(statement)){}

void ForStatement::execute(){
    // Variables::push();
    for(initialization->execute(); termination->eval()->as_number() != 0; increment->execute()){
        try{
            statement->execute();
        } catch (BreakStatement *bs){
            break;
        } catch (ContinueStatement *cs){
            // continue;
        }
    }
    // Variables::pop();
}

lets_str_t ForStatement::to_s(){
    
    lets_str_t result = "for " +
    initialization->to_s() + ", " +
    termination->to_s() + ", " +
    increment->to_s() + " " +
    statement->to_s();
    
    return result;
}

ForStatement::~ForStatement(){
    // delete[] initialization;
    // delete[] termination;
    // delete[] increment;
    // delete[] statement;
}
