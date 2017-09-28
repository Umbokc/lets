#ifndef TYPES_H
#define TYPES_H
#include <string>


enum Types {
	T_NUMBER,
	T_STRING,
	T_ARRAY,
	T_MAP,
	T_FUNCTION,

	T_REGEXP,
	T_MODULE,
	T_CLASS,
	T_INTERFACE,
	T_OBJECT,
	T_FILE,
};

const std::string TypesString[] {
	"number",
	"string",
	"array",
	"map",
	"function",

	"regexp",
	"module",
	"class",
	"interface",
	"object",
	"file",
};

#endif