//
//  s_return_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_return_stat.hpp"

ReturnStatement::ReturnStatement(Expression *expression){
    this->expression = expression;
}

Value *ReturnStatement::get_result(){
    return result;
}

void ReturnStatement::execute(){
    result = expression->eval();
    throw this;
}

lets_str_t ReturnStatement::to_s(){
    return "return";
}

ReturnStatement::~ReturnStatement(){
    // delete[] result;
    // delete[] expression;
}
