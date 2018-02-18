//
//  include/exception/error.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__exception__error_h
#define include__exception__error_h

#include <string>
#include "../main.h"

namespace ExceptionsError {
	const lets_str_t L_INVALID_FLOAT = "Invalid float number";
	const lets_str_t L_REACHED_EOF = "Reached end of file while parsing text string.";
	const lets_str_t L_MISS_CLOSE_TAG = "Missing close tag";
	const lets_str_t L_EOF_EXTEND_WORD = "Reached end of file while parsing extended word.";
	const lets_str_t L_EOL_EXTEND_WORD = "Reached end of line while parsing extended word.";

	const lets_str_t E_UNKNOWN_FUNC = "Unknown function '%s' ";
	const lets_str_t E_CNN_REWRITE_FUNC = "Cannot rewrite constant function '%s' ";
	const lets_str_t E_CNN_FUNC_TO_NUM = "Cannot cast function to number";
	const lets_str_t E_CNN_CLASS_TO_NUM = "Cannot cast class to number";
	const lets_str_t E_UNKNOWN_CLASS = "Unknown class '%s' ";
	const lets_str_t E_CNN_REWRITE_CLASS = "Class '%s' already exists";
	const lets_str_t E_CNN_REWRITE_CONSTANT = "Cannot assign value to constant '%s' ";

	const lets_str_t P_NULL_INDEX_ARR = "Undefined index of array";
	const lets_str_t P_ARGS_MISSMATCH = "Args count mismatch";
	const lets_str_t P_ARR_EXPECT = "Array expected";
	const lets_str_t P_CANNOT_RW_CONSTANTS = "Cannot assign value to constant '%s'";
	const lets_str_t P_CANNOT_RW_FUNC = "Cannot rewrite defined function '%s'";
	const lets_str_t P_ARR_TO_NUM = "Cannot cast array to number";
	const lets_str_t P_VAR_NULL = "Variable '%s' does not exists";
	const lets_str_t P_FUNC_NULL = "Undefined function '%s'";
	const lets_str_t P_MODULE_NULL = "Does not found module '%s'";
}

#endif /* include__exception__error_h */
