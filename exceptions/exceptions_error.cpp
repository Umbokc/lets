#include <string>

namespace ExceptionsError{
	const std::string L_INVALID_FLOAT = "Invalid float number";
	const std::string L_REACHED_EOF = "Reached end of file while parsing text string.";
	const std::string L_MISS_CLOSE_TAG = "Missing close tag";
	const std::string P_NULL_INDEX_ARR = "Undefined index of array";
	const std::string P_ARGS_MISSMATCH = "Args count mismatch";
	const std::string P_ARR_EXPECT = "Array expected";
	const std::string P_CANNOT_RW_CONSTANTS = "Cannot assign value to constant '%s'";
	const std::string P_CANNOT_RW_FUNC = "Cannot rewrite defined function '%s'";
	const std::string P_ARR_TO_NUM = "Cannot cast array to number";
	const std::string P_VAR_NULL = "Variable '%s' does not exists";
	const std::string P_FUNC_NULL = "Undefined function '%s'";
	const std::string P_MODULE_NULL = "Does not found module '%s'";
}