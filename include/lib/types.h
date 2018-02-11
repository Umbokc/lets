//
//  include/lib/types.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__types_h
#define include__lib__types_h

#include <string>
#include "../main.h"

enum Types {
	T_NULL,
	T_BOOL,
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

const lets_str_t TypesString[] = {
	"null",
	"bool",
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

#endif /* include__lib__types_h */
