//
//  o_variable_grabber.cpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/optimization/variable_grabber.hpp"
#include "../include/visitors/visitor_utils.h"

VariablesGrabber::VariablesGrabber():grab_module_constants(false) {}
VariablesGrabber::VariablesGrabber(bool gmc):grab_module_constants(std::move(gmc)) {}
VariablesGrabber::~VariablesGrabber(){}

VariablesGrabber::THE_TYPE VariablesGrabber::getInfo(Node *node) {
	return getInfo(node, false);
}

VariablesGrabber::THE_TYPE VariablesGrabber::getInfo(Node *node, bool grab_module_constants) {
	THE_TYPE variable_infos;
	node->accept(node, new VariablesGrabber(grab_module_constants), variable_infos);
	return variable_infos;
}

Node *VariablesGrabber::visit(AssignmentExpression *s, THE_TYPE t) {
	if (!VisitorUtils::is_variable(dynamic_cast<Node*>(s->target))) {
		return OptimizationVisitor::visit(s, t);
	}

	lets_str_t variable_name = dynamic_cast<VariableExpression*>(s->target)->name;
	VariableInfo *var = variable_info(t, variable_name);

	if (s->operation == NS_Binary::Operator::THE_NULL && VisitorUtils::is_value(s->expression)) {
		var->value = dynamic_cast<ValueExpression*>(s->expression)->value;
	}

	t[variable_name] = var;
	return OptimizationVisitor::visit(s, t);
}

Node *VariablesGrabber::visit(ForeachStatement *s, THE_TYPE t) {
	t[s->key] = variable_info(t, s->key);
	t[s->val] = variable_info(t, s->val);
	return OptimizationVisitor::visit(s, t);
}

// 	Node *visit(MatchExpression s, THE_TYPE t) {
// 		for (MatchExpression.Pattern pattern : s->patterns) {
// 			if (pattern instanceof MatchExpression.VariablePattern) {
// 				lets_str_t variable_name = ((MatchExpression.VariablePattern) pattern).variable;
// 				t.put(variable_name, variable_info(t, variable_name));
// 			}
// 		}
// 		return OptimizationVisitor::visit(s, t);
// 	}

Node *VariablesGrabber::visit(UnaryExpression *s, THE_TYPE t) {
	if (dynamic_cast<Accessible*>(s->expr)) {
		if (dynamic_cast<VariableExpression*>(s->expr)) {
			lets_str_t variable_name = (dynamic_cast<VariableExpression*>(s->expr))->name;
			t[variable_name] = variable_info(t, variable_name);
		}
		if (dynamic_cast<ContainerAccessExpression*>(s->expr)) {
			ContainerAccessExpression *conExpr = dynamic_cast<ContainerAccessExpression*>(s->expr);
			if (conExpr->root_is_variable()) {
				lets_str_t variable_name = (dynamic_cast<VariableExpression*>(conExpr->root))->name;
				t[variable_name] = variable_info(t, variable_name);
			}
		}
	}
	return OptimizationVisitor::visit(s, t);
}

// Node *visit(UseStatement* s, THE_TYPE t) {
	// if (grab_module_constants) {
	// 		// To get module variables we need  to store current variables, clear all, then load module.
	// 	lets_map_t<lets_str_t, Value*> current_variables = Variables::variables();
	// 	Variables->variables().clear();
	// 	if (isValue(s->expression)) {
	// 		s->loadConstants();
	// 	}
	// 		// Grab module variables
	// 	for (Map.Entry<lets_str_t, Value*> entry : Variables->variables().entrySet()) {
	// 		VariableInfo *var = variable_info(t, entry.getKey());
	// 		var.value = entry.getValue();
	// 		t.put(entry.getKey(), var);
	// 	}
	// 	// Restore previous variables
	// 	Variables->variables().putAll(current_variables);
	// }
	// return OptimizationVisitor::visit(s, t);
// }

bool VariablesGrabber::visit_t(Arguments in, Arguments out, THE_TYPE t) {
	for (int i = 0; i < in.get_size(); ++i) {
		Argument argument = in.get(i);
		lets_str_t variable_name = argument.get_name();
		VariableInfo *var = variable_info(t, variable_name);
					/* No need to add value - it is optional arguments
						Expression expr = argument.getValueExpr();
						if (expr != NULL && isValue(expr)) {
								var.value = ((ValueExpression) expr).value;
						}*/
		t[variable_name] = var;
	}
	return OptimizationVisitor::visit_t(in, out, t);
}

VariableInfo *VariablesGrabber::variable_info(THE_TYPE t, lets_str_t variable_name) {
	VariableInfo *var;
	if (t.find(variable_name) != t.end()) {
		var = t[variable_name];
		var->modifications++;
	} else {
		var = new VariableInfo();
		var->modifications = 1;
	}
	return var;
}