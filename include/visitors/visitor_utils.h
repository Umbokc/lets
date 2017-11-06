//
//  visitors/visitor_utils.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__visitor_utils_h
#define visitors__visitor_utils_h

#include <string>
#include <vector>
#include "../main.h"

#include "../e_binary_expr.hpp"
#include "../e_conditional_expr.hpp"
#include "../e_unary_expr.hpp"
#include "../e_value_expr.hpp"
#include "../e_variable_expr.hpp"


namespace VisitorUtils {
	
	static bool is_value(Node* node) {
		return dynamic_cast<ValueExpression*>(node);
	}

	static bool is_variable(Node* node) {
		return dynamic_cast<VariableExpression*>(node);
	}

	// static Statement include_program(IncludeStatement s) {
	// 	if (!is_value(s)) return null;
	// 	try {
	// 		return s.loadProgram(s.expression.eval().asString());
	// 	} catch (IOException ex) {
	// 		return null;
	// 	}
	// }

	// static bool is_integer_value(Node node, int valueToCheck) {
	// 	if (!is_value(node)) return false;

	// 	final Value value = ((ValueExpression) node).value;
	// 	if (value.type() != Types.NUMBER) return false;

	// 	final Number number = ((NumberValue) value).raw();
	// 	if ( (number instanceof Integer) || (number instanceof Short) || (number instanceof Byte)) {
	// 		return number.intValue() == valueToCheck;
	// 	}
	// 	return false;
	// }

	// static bool is_valueasint(Node node, int valueToCheck) {
	// 	if (!is_value(node)) return false;

	// 	final Value value = ((ValueExpression) node).value;
	// 	if (value.type() != Types.NUMBER) return false;

	// 	return value.asInt() == valueToCheck;
	// }

	// static bool is_constant_value(Node node) {
	// 	if (!is_value(node)) return false;

	// 	final int type = ((ValueExpression) node).value.type();
	// 	return ( (type == Types.NUMBER) || (type == Types.STRING) );
	// }

	// static bool is_same_variables(Node n1, Node n2) {
	// 	if (is_variable(n1) && is_variable(n2)) {
	// 		final VariableExpression v1 = (VariableExpression) n1;
	// 		final VariableExpression v2 = (VariableExpression) n2;
	// 		return v1.name.equals(v2.name);
	// 	}
	// 	return false;
	// }

	static lets_vector_t<lets_str_t> operators() {
		lets_vector_t<lets_str_t> operators;
		for (lets_str_t op : NS_Binary::OperatorString) {
			operators.push_back(op);
		}
		for (lets_str_t op : NS_Unary::OperatorString) {
			operators.push_back(op);
		}
		for (lets_str_t op : NS_Conditional::OperatorString) {
			operators.push_back(op);
		}
		return operators;
	}
};

#endif /* visitors__visitor_utils_h */

