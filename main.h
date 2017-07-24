#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <string>
#include <vector>

#include "declaration.h"
#include "functions.h"

#include "exceptions/exceptions_error.cpp"
#include "exceptions/parse_exception.cpp"

#include "lib/types.h"
#include "lib/value.h"
#include "lib/function.h"
#include "lib/number_value.h"
#include "lib/string_value.h"
#include "lib/variables.h"
#include "lib/array_value.h"
#include "lib/functions.h"

#include "parser/tokentype.h"
#include "parser/token.h"
#include "parser/lexer.cpp"

#include "parser/ast/main/visitor.h"
#include "parser/ast/main/node.h"

#include "parser/ast/main/expression.h"
#include "parser/ast/expressions/value_expression.cpp"
#include "parser/ast/expressions/array_access_expression.cpp"
#include "parser/ast/expressions/array_expression.cpp"
#include "parser/ast/expressions/binary_expression.cpp"
#include "parser/ast/expressions/conditional_expression.cpp"
#include "parser/ast/expressions/unary_expression.cpp"
#include "parser/ast/expressions/ternary_expression.cpp"
#include "parser/ast/expressions/variable_xpression.cpp"


#include "parser/ast/main/statement.h"
#include "parser/ast/statements/break_statement.cpp"
#include "parser/ast/statements/continue_statement.cpp"
#include "parser/ast/statements/block_statement.cpp"
#include "parser/ast/statements/assignment_statement.cpp"
#include "parser/ast/statements/array_assignment_statement.cpp"
#include "parser/ast/statements/return_statement.cpp"
#include "parser/ast/statements/for_statement.cpp"
#include "parser/ast/statements/do_while_statement.cpp"
#include "parser/ast/statements/while_statement.cpp"
#include "parser/ast/statements/if_statement.cpp"
#include "parser/ast/statements/print_statement.cpp"
#include "parser/ast/statements/println_statement.cpp"

#include "lib/user_define_function.h"
#include "parser/ast/expressions/functional_expression.cpp"

#include "parser/ast/statements/function_define_statement.cpp"
#include "parser/ast/statements/function_statement.cpp"

#include "modules/std/std_module.h"
#include "modules/math/math_module.h"
#include "parser/ast/statements/use_statement.cpp"

#include "parser/parser.cpp"

#include "lets.h"

#endif