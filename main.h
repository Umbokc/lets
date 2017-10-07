#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <string>
#include <vector>

#include "include/help_functions.cpp"

#include "utils/time_measurement.cpp"

#include "include/mode.h"

#include "include/declaration.h"

#include "exceptions/exceptions_error.cpp"
#include "exceptions/parse_exception.cpp"
#include "exceptions/variable_does_not_exists_exception.cpp"

#include "lib/types.h"
#include "lib/arguments_check.h"
#include "lib/value.h"
#include "lib/function.h"
#include "lib/number.h"
#include "lib/number_value.h"
#include "lib/string_value.h"
#include "lib/variables.h"
#include "lib/array_value.h"
#include "lib/functions.h"
#include "lib/function_value.h"
#include "lib/call_stack.cpp"
#include "lib/map_value.h"


#include "include/tokentype.h"
#include "include/token.cpp"
#include "lexer.cpp"

#include "include/visitor.h"
#include "include/node.h"
#include "include/accessible.h"

#include "include/expression.h"
#include "include/statement.h"

#include "argument.cpp"
#include "arguments.cpp"

#include "value_expression.cpp"
#include "array_access_expression.cpp"
#include "array_expression.cpp"
#include "map_expression.cpp"
#include "binary_expression.cpp"
#include "conditional_expression.cpp"
#include "unary_expression.cpp"
#include "ternary_expression.cpp"
#include "variable_expression.cpp"
#include "assignment_expression.cpp"
#include "container_access_expression.cpp"
#include "input_expression.cpp"
#include "match_expression.cpp"


#include "break_statement.cpp"
#include "continue_statement.cpp"
#include "block_statement.cpp"
#include "assignment_statement.cpp"
#include "array_assignment_statement.cpp"
#include "return_statement.cpp"
#include "for_statement.cpp"
#include "foreach_statement.cpp"
#include "do_while_statement.cpp"
#include "while_statement.cpp"
#include "if_statement.cpp"
#include "print_statement.cpp"
#include "put_statement.cpp"
#include "mode_programm_statment.cpp"

#include "lib/user_define_function.h"
#include "functional_expression.cpp"

#include "function_define_statement.cpp"
#include "expr_statement.cpp"

#include "use_statement.cpp"

#include "parser.cpp"

// #include "include/lets.cpp"

class Options {
	bool showTokens = false, showAst = false, showMeasurements = false;
	bool lintMode = false;
	int optimizationLevel = 0;
public:
	void validate() {
		if (lintMode == true) {
			showTokens = false;
			showAst = false;
			showMeasurements = false;
			optimizationLevel = 0;
		}
	}
};

#endif