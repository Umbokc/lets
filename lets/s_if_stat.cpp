//
//  s_if_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_if_stat.hpp"

IfStatement::IfStatement(Expression *expression, Statement *if_statement, Statement *else_statement):
expression(std::move(expression)), if_statement(std::move(if_statement)), else_statement(std::move(else_statement))
{}

void IfStatement::execute(){
    double result = expression->eval()->as_number();
    if(result != 0){
        if_statement->execute();
    } else if(else_statement != NULL){
        else_statement->execute();
    }
}

lets_str_t IfStatement::to_s(){
    lets_str_t result = "";
    result += "if ";
    result += expression->to_s();
    result += " ";
    result += if_statement->to_s();
    if(else_statement != NULL){
        result += "\nelse ";
        result += else_statement->to_s();
    }
    
    return result;
}

IfStatement::~IfStatement(){
    // delete[] expression;
    // delete[] if_statement;
    // delete[] else_statement;
}
