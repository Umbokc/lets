//
//  include/optimization/summary_optimization.hpp
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__optimization__summary_optimization_hpp
#define include__optimization__summary_optimization_hpp

#include <vector>
#include <string>
#include "../main.h"
#include "optimizable.h"

class SummaryOptimization : public Optimizable{
private:
	lets_vector_t<Optimizable*> optimizations;
	int size;
public:

	SummaryOptimization();
	SummaryOptimization(lets_vector_t<Optimizable*>);

	Node *optimize(Node *);
	int optimizations_count();
	lets_str_t summary_info();

	~SummaryOptimization();
};

#endif /* include__optimization__summary_optimization_hpp */

