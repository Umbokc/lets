#ifndef LL_UTIL_SUMMARY_OPTIMIZATION_CPP
#define LL_UTIL_SUMMARY_OPTIMIZATION_CPP

#include <vector>
#include "optimizable.h"

class SummaryOptimization : public Optimizable{
private:
	std::vector<Optimizable*> optimizations;
	int size;
public:

	SummaryOptimization(){}

	SummaryOptimization(std::vector<Optimizable*> optimizations):optimizations(std::move(optimizations)) {
		this->size = this->optimizations.size();
	}

	Statement *optimize(Statement *statement) {
		for(int i = 0; i < this->size; i++){
			statement = optimizations[i]->optimize(statement);
		}
		return statement;
	}

	int optimizations_count() {
		int count = 0;
		for(int i = 0; i < this->size; i++){
			count += optimizations[i]->optimizations_count();
		}
		return count;
	}

	std::string summary_info() {
		std::string sb;
		for(int i = 0; i < this->size; i++){
			sb += optimizations[i]->summary_info();
		}
		return sb;
	}

	~SummaryOptimization(){}
};

#endif