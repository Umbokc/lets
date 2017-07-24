#ifndef TYPES_H
#define TYPES_H
#include <string>

enum Types {
	T_NUMBER,
	T_STRING,
	T_ARRAY,
	T_FUNCTION,
};

const std::string TypesString[] {
	"number",
	"string",
	"array",
	"function",
};

#endif