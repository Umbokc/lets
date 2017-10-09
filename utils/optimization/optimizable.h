#ifndef LL_UTIL_OPTIMIZABLE_H
#define LL_UTIL_OPTIMIZABLE_H

class Optimizable {
public:
	virtual Statement *optimize(Statement *statement) = 0;
	virtual int optimizations_count() = 0;
	virtual std::string summary_info() = 0;
};

#endif