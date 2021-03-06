//
//  lets/visitors/visitor_utils.cpp
//  lets
//
//  Created by Dragan Stepan on 17.11.17.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include "../../include/visitors/visitor_utils.hpp"
#include "../../include/expressions/binary_expr.hpp"
#include "../../include/expressions/conditional_expr.hpp"
#include "../../include/expressions/unary_expr.hpp"
#include "../../include/expressions/value_expr.hpp"
#include "../../include/expressions/variable_expr.hpp"

bool VisitorUtils::is_value(Node* node) {
	return dynamic_cast<ValueExpression*>(node);
}

bool VisitorUtils::is_variable(Node* node) {
	return dynamic_cast<VariableExpression*>(node);
}

// Statement* VisitorUtils::include_program(IncludeStatement* s) {
// 	if (!is_value(s)) return null;
// 	try {
// 		return s.loadProgram(s.expression.eval().asString());
// 	} catch (IOException ex) {
// 		return null;
// 	}
// }

// bool VisitorUtils::is_integer_value(Node *node, int valueToCheck) {
// 	if (!is_value(node)) return false;

// 	final Value value = ((ValueExpression) node).value;
// 	if (value.type() != Types.NUMBER) return false;

// 	final Number number = ((NumberValue) value).raw();
// 	if ( (number instanceof Integer) || (number instanceof Short) || (number instanceof Byte)) {
// 		return number.intValue() == valueToCheck;
// 	}
// 	return false;
// }

// bool VisitorUtils::is_valueasint(Node *node, int valueToCheck) {
// 	if (!is_value(node)) return false;

// 	final Value value = ((ValueExpression) node).value;
// 	if (value.type() != Types.NUMBER) return false;

// 	return value.asInt() == valueToCheck;
// }

// bool VisitorUtils::is_constant_value(Node *node) {
// 	if (!is_value(node)) return false;

// 	final int type = ((ValueExpression) node).value.type();
// 	return ( (type == Types.NUMBER) || (type == Types.STRING) );
// }

// bool VisitorUtils::is_same_variables(Node *n1, Node *n2) {
// 	if (is_variable(n1) && is_variable(n2)) {
// 		final VariableExpression v1 = (VariableExpression) n1;
// 		final VariableExpression v2 = (VariableExpression) n2;
// 		return v1.name.equals(v2.name);
// 	}
// 	return false;
// }

lets_vector_t<lets_str_t> VisitorUtils::operators() {
	lets_vector_t<lets_str_t> operators;
	for (lets_str_t op : NS_Binary::OperatorString) {
		operators.push_back(op);
	}
	for (lets_str_t op : UnaryExpression::OperatorString) {
		operators.push_back(op);
	}
	for (lets_str_t op : ConditionalExpression::OperatorString) {
		operators.push_back(op);
	}
	return operators;
}