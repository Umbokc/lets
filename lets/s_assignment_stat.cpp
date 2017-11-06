//
//  s_assignment_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_assignment_stat.hpp"
#include "../include/l_variables.h"

    
AssignmentStatement::AssignmentStatement(lets_str_t variable, Expression* expression){
    this->variable = variable;
    this->expression = expression;
}

void AssignmentStatement::execute(){
    Value* result = expression->eval();
    Variables::set(variable, result);
}

lets_str_t AssignmentStatement::to_s(){
    return variable + " = " + expression->to_s();
}

AssignmentStatement::~AssignmentStatement(){
    // delete[] expression;
}
