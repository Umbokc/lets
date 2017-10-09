#ifndef LL_UTIL_OPTIMIZER_H
#define LL_UTIL_OPTIMIZER_H

#include <vector>
#include "optimizable.h"
#include "summary_optimization.cpp"
#include "methods/constant_folding.cpp"

namespace Optimizer {
	static Statement* optimize(Statement *statement, int level, bool showSummary) {
		if (level == 0) return statement;
		
		std::vector<Optimizable*> all_opt = {
			new ConstantFolding()
			// new ConstantPropagation(),
			// new DeadCodeElimination(),
			// new ExpressionSimplification(),
			// new InstructionCombining()
		};

		Optimizable* optimization = new SummaryOptimization(all_opt);

		// Node *result = dynamic_cast<Node*>(statement);
		Statement *result = statement;

		if (level >= 9) {
			int iteration = 0, lastModifications = 0;
			do {
				lastModifications = optimization->optimizations_count();
				result = optimization->optimize(result);
				iteration++;
			} while (lastModifications != optimization->optimizations_count());
			if (showSummary)
				std::cout << "Performs " << iteration << " optimization iterations";
		} else {
			for (int i = 0; i < level; i++) {
				result = optimization->optimize(result);
			}
		}
		if (showSummary) {
			std::cout << optimization->summary_info() << std::endl;
		}
		// return dynamic_cast<Statement*>(result);
		return result;
	}
}

#endif