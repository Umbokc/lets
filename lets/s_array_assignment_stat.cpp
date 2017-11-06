//
//  s_array_assignment_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_array_assignment_stat.hpp"

    
ArrayAssignmentStatement::ArrayAssignmentStatement(ArrayAccessExpression *array, Expression *expression){
    this->array = array;
    this->expression = expression;
}

void ArrayAssignmentStatement::execute(){
    array->get_array()->set(array->last_index(),expression->eval());
}

lets_str_t ArrayAssignmentStatement::to_s(){
    return array->to_s() + " = " + expression->to_s();
}

ArrayAssignmentStatement::~ArrayAssignmentStatement(){
    // delete[] expression;
    // delete[] array;
}

