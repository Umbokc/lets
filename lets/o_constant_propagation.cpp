//
//  o_constant_propagation.cpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/optimization/methods/constant_propagation.hpp"
#include "../include/optimization/variable_grabber.hpp"

Node *ConstantPropagation::optimize(Node *node) {
	lets_map_t<lets_str_t, VariableInfo*> variables;
	// Find variables
	node->accept(node, new VariablesGrabber(true), variables);
	// Filter only lets_str_t/number values with 1 modification
	THE_TYPE candidates;
	for (auto& e : variables) {
		VariableInfo* info = e.second;
		if (info->modifications != 1) continue;
		if (info->value == NULL) continue;
		switch (info->value->type()) {
			case Types::T_NUMBER:
			case Types::T_STRING:
				candidates[e.first] = info->value;
			break;
			default:
			break;
		}
	}
// Replace VariableExpression with ValueExpression
	return node->accept(node, this, candidates);
}

int ConstantPropagation::optimizations_count() {
	return propagated_variables.size();
}

lets_str_t ConstantPropagation::summary_info() {
	if (optimizations_count() == 0) return "";
	lets_str_t sb;
	if (propagated_variables.size() > 0) {
		sb = "\nConstant propagations: ";
		sb += std::to_string(propagated_variables.size());
		for (auto& entry : propagated_variables) {
				sb+= "\n" + entry.first + ": "  += std::to_string(entry.second);
		}
	}
	return sb;
}

Node *ConstantPropagation::visit(VariableExpression *s, THE_TYPE t) {
	if (t.find(s->name) != t.end()) {
		if (propagated_variables.find(s->name) == propagated_variables.end()) {
			propagated_variables[s->name] = 1;
		} else {
			propagated_variables[s->name] = 1 + propagated_variables[s->name];
		}
		return new ValueExpression(t[s->name]);
	}
	return OptimizationVisitor::visit(s, t);
}