//
//  o_optimizer.cpp
//  lets
//
//  Created by Dragan Stepan on 17.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/optimization/optimizer.h"
#include "../include/optimization/optimizable.h"
#include "../include/optimization/summary_optimization.hpp"

#include "../include/optimization/methods/constant_folding.hpp"
#include "../include/optimization/methods/constant_propagation.hpp"

Statement* Optimizer::optimize(Statement *statement, int level, bool show_summary) {
	if (level == 0) return statement;

	lets_vector_t<Optimizable*> all_opt = {
		new ConstantFolding(),
		new ConstantPropagation(),
			// new DeadCodeElimination(),
			// new ExpressionSimplification(),
			// new InstructionCombining()
	};

	Optimizable* optimization = new SummaryOptimization(all_opt);

	Node *result = statement;

	if (level >= 9) {
		int iteration = 0, last_modifications = 0;
		do {
			last_modifications = optimization->optimizations_count();
			result = optimization->optimize(result);
			iteration++;
		} while (last_modifications != optimization->optimizations_count());
		if (show_summary)
			lets_output("Performs " << iteration << " optimization iterations")
	} else {
		for (int i = 0; i < level; i++) {
			result = optimization->optimize(result);
		}
	}
	if (show_summary) {
		lets_output(optimization->summary_info())
	}
	return dynamic_cast<Statement*>(result);
}