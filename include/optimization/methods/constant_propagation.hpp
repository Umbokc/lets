//
//  include/optimization/methods/constant_propagation.hpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__optimization__methods__constant_propagation_hpp
#define include__optimization__methods__constant_propagation_hpp

#include "../optimizable.h"
#include "../../visitors/optimization_visitor.h"

class ConstantPropagation : 
	virtual public OptimizationVisitor<lets_map_t<lets_str_t, Value*>>,
	public Optimizable
{
private:
	lets_map_t<lets_str_t, int> propagated_variables;
public:
	typedef lets_map_t<lets_str_t, Value*> THE_TYPE;

	ConstantPropagation(){}
	~ConstantPropagation(){}

	Node *optimize(Node*);
	int optimizations_count();
	lets_str_t summary_info();

	Node *visit(VariableExpression*, THE_TYPE&);

};


#endif /* include__optimization__methods__constant_propagation_hpp */

