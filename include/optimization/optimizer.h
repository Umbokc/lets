//
//  optimization/optimizer.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef optimization__optimizer_h
#define optimization__optimizer_h

#include "optimizable.h"
#include "summary_optimization.hpp"

#include "methods/constant_folding.hpp"
#include "methods/constant_propagation.hpp"

namespace Optimizer {
	static Statement* optimize(Statement *statement, int level, bool show_summary) {
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
}

#endif /* optimization__optimizer_h */

