//
//  optimization/methods/constant_folding.hpp
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef optimization__methods__constant_folding_hpp
#define optimization__methods__constant_folding_hpp

#include "../optimizable.h"
#include "../../visitors/optimization_visitor.h"

class ConstantFolding : virtual public OptimizationVisitor<bool>, public Optimizable {
private:
	int binary_expression_folding_count;
	int conditional_expression_folding_count;
	int unary_expression_folding_count;
	lets_vector_t<lets_str_t> overloaded_operators;
	static lets_vector_t<lets_str_t> OPERATORS;
public:

	ConstantFolding();

	Node *optimize(Node *);
	int optimizations_count();
	lets_str_t summary_info();

	Node *visit(BinaryExpression*, bool);
	Node *visit(ConditionalExpression*, bool);
	Node *visit(UnaryExpression*, bool);
	Node *visit(FunctionDefineStatement*, bool);

private:

	bool operators_contains(lets_str_t);
	bool overloaded_operators_contains(lets_str_t);

};

#endif /* optimization__methods__constant_folding_hpp */

