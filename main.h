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
#include "exceptions/operation_is_not_supported_exception.cpp"

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

#include "include/node.h"
#include "include/accessible.h"

#include "include/expression.h"
#include "include/statement.h"

#include "ast/argument.cpp"
#include "ast/arguments.cpp"

#include "ast/expressions/value_expression.cpp"
#include "ast/expressions/array_access_expression.cpp"
#include "ast/expressions/array_expression.cpp"
#include "ast/expressions/map_expression.cpp"
#include "ast/expressions/binary_expression.cpp"
#include "ast/expressions/conditional_expression.cpp"
#include "ast/expressions/unary_expression.cpp"
#include "ast/expressions/ternary_expression.cpp"
#include "ast/expressions/variable_expression.cpp"
#include "ast/expressions/assignment_expression.cpp"
#include "ast/expressions/container_access_expression.cpp"
#include "ast/expressions/input_expression.cpp"
#include "ast/expressions/match_expression.cpp"


#include "ast/statements/break_statement.cpp"
#include "ast/statements/continue_statement.cpp"
#include "ast/statements/block_statement.cpp"
#include "ast/statements/assignment_statement.cpp"
#include "ast/statements/array_assignment_statement.cpp"
#include "ast/statements/return_statement.cpp"
#include "ast/statements/for_statement.cpp"
#include "ast/statements/foreach_statement.cpp"
#include "ast/statements/do_while_statement.cpp"
#include "ast/statements/while_statement.cpp"
#include "ast/statements/if_statement.cpp"
#include "ast/statements/print_statement.cpp"
#include "ast/statements/put_statement.cpp"
#include "ast/statements/mode_programm_statement.cpp"
#include "ast/statements/self_statement.cpp"

#include "lib/user_define_function.h"
#include "ast/expressions/functional_expression.cpp"

#include "ast/statements/function_define_statement.cpp"
#include "ast/statements/expr_statement.cpp"

#include "ast/statements/use_statement.cpp"

#include "parser.cpp"

#include "utils/optimization/optimizer.cpp"

// #include "include/lets.cpp"

// class Options {
// 	bool showTokens = false, showAst = false, showMeasurements = false;
// 	bool lintMode = false;
// 	int optimizationLevel = 0;
// public:
// 	void validate() {
// 		if (lintMode == true) {
// 			showTokens = false;
// 			showAst = false;
// 			showMeasurements = false;
// 			optimizationLevel = 0;
// 		}
// 	}
// };

#endif