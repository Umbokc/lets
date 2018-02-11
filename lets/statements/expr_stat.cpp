//
//  lets/statements/expr_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/statements/expr_stat.hpp"

ExprStatement::ExprStatement(Expression *function): expr(std::move(function)){}

void ExprStatement::execute(){
	eval();
}


Value *ExprStatement::eval(){
	return expr->eval();
}


lets_str_t ExprStatement::to_s(){
	return expr->to_s();
}

ExprStatement::~ExprStatement(){}
