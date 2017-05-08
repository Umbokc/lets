#ifndef LIB_CLASSES_H
#define LIB_CLASSES_H

#include "Value.h"
#include "StringValue.h"
#include "NumberValue.h"
#include "Variables.h"
#include "ArrayValue.h"
#include "Function.h"


class Functions{
public:
	static bool isExists(std::string key);
	static Function* get(std::string key);
	static void set(std::string key, Function* function);
	~Functions();
};

#include "Functions.h"

#endif
