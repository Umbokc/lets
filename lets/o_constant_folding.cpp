//
//  o_constant_folding.cpp
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/optimization/methods/constant_folding.hpp"
#include "../include/visitors/visitor_utils.h"
#include "../include/ex_operation_is_not_supported.h"

lets_vector_t<lets_str_t> ConstantFolding::OPERATORS = VisitorUtils::operators();

ConstantFolding::ConstantFolding() {}

Node *ConstantFolding::optimize(Node *node) {
	return node->accept(node, this, false);
}

int ConstantFolding::optimizations_count() {
	return binary_expression_folding_count
	+ conditional_expression_folding_count
	+ unary_expression_folding_count;
}

lets_str_t ConstantFolding::summary_info() {
	if (optimizations_count() == 0) return "";

	lets_str_t sb;

	if (binary_expression_folding_count > 0) {
		sb += "\nBinaryExpression foldings: ";
		sb += std::to_string(binary_expression_folding_count);
	}
	if (conditional_expression_folding_count > 0) {
		sb += "\nConditionalExpression foldings: ";
		sb += std::to_string(conditional_expression_folding_count);
	}
	if (unary_expression_folding_count > 0) {
		sb += "\nUnaryExpression foldings: ";
		sb += std::to_string(unary_expression_folding_count);
	}

	return sb;
}

Node *ConstantFolding::visit(BinaryExpression *s, bool t) {
	if (overloaded_operators_contains(NS_Binary::OperatorString[s->operation])) {
		return OptimizationVisitor::visit(s, t);
	}
	if ( dynamic_cast<ValueExpression*>(s->expr1) && dynamic_cast<ValueExpression*>(s->expr2) ) {
		binary_expression_folding_count++;
		try {
			return new ValueExpression(s->eval());
		} catch (OperationIsNotSupportedException& op) {
			binary_expression_folding_count--;
		}
	}
	
	return OptimizationVisitor::visit(s, t);
}

Node *ConstantFolding::visit(ConditionalExpression *s, bool t) {
	if (overloaded_operators_contains(ConditionalExpression::OperatorString[s->operation])) {
		return OptimizationVisitor::visit(s, t);
	}
	if ( dynamic_cast<ValueExpression*>(s->expr1) && dynamic_cast<ValueExpression*>(s->expr2) ) {
		conditional_expression_folding_count++;
		try {
			return new ValueExpression(s->eval());
		} catch (OperationIsNotSupportedException& op) {
			conditional_expression_folding_count--;
		}
	}
	return OptimizationVisitor::visit(s, t);
}

Node *ConstantFolding::visit(UnaryExpression* s, bool t) {
	if (overloaded_operators_contains(UnaryExpression::OperatorString[s->operation])) {
		return OptimizationVisitor::visit(s, t);
	}
	if (dynamic_cast<ValueExpression*>(s->expr)) {
		unary_expression_folding_count++;
		try {
			return new ValueExpression(s->eval());
		} catch (OperationIsNotSupportedException& op) {
			unary_expression_folding_count--;
		}
	}
	return OptimizationVisitor::visit(s, t);
}

Node *ConstantFolding::visit(FunctionDefineStatement *s, bool t) {
	if (operators_contains(s->name)) {
		overloaded_operators.push_back(s->name);
	}
	return OptimizationVisitor::visit(s, t);
}

bool ConstantFolding::operators_contains(lets_str_t val) {
	return find(OPERATORS.begin(), OPERATORS.end(), val) != OPERATORS.end();
}
bool ConstantFolding::overloaded_operators_contains(lets_str_t val) {
	return find(overloaded_operators.begin(), overloaded_operators.end(), val) != overloaded_operators.end();
}
