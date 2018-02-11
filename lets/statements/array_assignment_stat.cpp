//
//  lets/statements/array_assignment_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/statements/array_assignment_stat.hpp"


ArrayAssignmentStatement::ArrayAssignmentStatement(ArrayAccessExpression *array, Expression *expression):
	array(std::move(array)), expression(std::move(expression)){}

void ArrayAssignmentStatement::execute(){
	array->get_array()->set(array->last_index(),expression->eval());
}

lets_str_t ArrayAssignmentStatement::to_s(){
	return array->to_s() + " = " + expression->to_s();
}

ArrayAssignmentStatement::~ArrayAssignmentStatement(){}
