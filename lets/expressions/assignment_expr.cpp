//
//  lets/expressions/assignment_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/assignment_expr.hpp"
#include "../../include/expressions/value_expr.hpp"
#include "../../include/tools.hpp"

AssignmentExpression::AssignmentExpression(
	NS_Binary::Operator operation, Accessible *target, Expression *expression) :
	operation(operation), target(std::move(target)), expression(std::move(expression)){}

void AssignmentExpression::execute(){
	eval();
}

Value* AssignmentExpression::eval(){

	if(operation == NS_Binary::Operator::THE_NULL){
		return target->set(expression->eval());
	}

	Expression *expr1 = new ValueExpression(target->get());
	Expression *expr2 = new ValueExpression(expression->eval());
	Expression *res_expr = new BinaryExpression(operation, expr1, expr2);

	Value *result = target->set(res_expr->eval());

	return result;
}

lets_str_t AssignmentExpression::to_s(){
	return NS_Tools::string_format(
		"%s %s %s",
		target->to_s().c_str(),
		NS_Binary::OperatorString[operation].c_str(),
		expression->to_s().c_str()
	);
}
AssignmentExpression::~AssignmentExpression(){
	// delete[] target;
	// delete[] falseExpr;
}
