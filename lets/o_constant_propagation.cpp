//
//  o_constant_propagation.cpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg
#include "../include/optimization/methods/constant_propagation.hpp"
#include "../include/optimization/variable_grabber.hpp"


Node *ConstantPropagation::optimize(Node *node) {
	lets_map_t<lets_str_t, VariableInfo> variables;
	// Find variables
	node->accept(new VariablesGrabber(true), variables);
	// Filter only lets_str_t/number values with 1 modification
	THE_TYPE candidates;
	for (auto e : variables) {
		VariableInfo info = e.second;
		if (info.modifications != 1) continue;
		if (info.value == NULL) continue;
		switch (info.value->type()) {
			case Types::T_NUMBER:
			case Types::T_STRING:
				candidates[e.first] = info.value;
				break;
		}
	}
// Replace VariableExpression with ValueExpression
	return node->accept(this, candidates);
}

int ConstantPropagation::optimizations_count() {
	return this->propagated_variables.size();
}

lets_str_t ConstantPropagation::summary_info() {
	if (optimizations_count() == 0) return "";
	lets_str_t sb;
	if (this->propagated_variables.size() > 0) {
		sb = "\nConstant propagations: ";
		sb += to_str(this->propagated_variables.size());
		// for (auto& entry : this->propagated_variables) {
		// 		sb+= "\n" + entry.first + ": "  += to_str(entry.second);
		// }
	}
	return sb;
}

Node *ConstantPropagation::visit(VariableExpression *s, THE_TYPE& t) {
	if (t.find(s->name) != t.end()) {
		if (this->propagated_variables.find(s->name) == this->propagated_variables.end()) {
			this->propagated_variables[s->name] = 1;
		} else {
			this->propagated_variables[s->name] = 1 + this->propagated_variables[s->name];
		}
		return new ValueExpression(t[s->name]);
	}
	return OptimizationVisitor::visit(s, t);
}