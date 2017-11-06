//
//  o_summary_optimization.cpp
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/optimization/summary_optimization.hpp"

SummaryOptimization::SummaryOptimization(){}

SummaryOptimization::SummaryOptimization(lets_vector_t<Optimizable*> optimizations):optimizations(std::move(optimizations)) {
	this->size = (int)this->optimizations.size();
}

Node *SummaryOptimization::optimize(Node *node) {
	for(int i = 0; i < this->size; i++){
		node = optimizations[i]->optimize(node);
	}
	return node;
}

int SummaryOptimization::optimizations_count() {
	int count = 0;
	for(int i = 0; i < this->size; i++){
		count += optimizations[i]->optimizations_count();
	}
	return count;
}

lets_str_t SummaryOptimization::summary_info() {
	lets_str_t sb;
	for(int i = 0; i < this->size; i++){
		sb += optimizations[i]->summary_info();
	}
	return sb;
}

SummaryOptimization::~SummaryOptimization(){}

