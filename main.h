#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstring>
#include <cstdlib>	
#include <vector>
#include <locale>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <stdarg.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "dop_func.h"

#include "lib/Value.h"
#include "lib/StringValue.h"
#include "lib/NumberValue.h"
#include "lib/ArrayValue.h"
#include "lib/Variables.h"
#include "lib/Function.h"
#include "lib/Functions.h"


#include "parser/TokenType.h"
#include "parser/Token.h"
#include "parser/Lexer.h"

#include "parser/ast/Expression.h"
#include "parser/ast/ValueExpression.h"
#include "parser/ast/BinaryExpression.h"
#include "parser/ast/UnaryExpression.h"
#include "parser/ast/VariableExpression.h"
#include "parser/ast/ConditionalExpression.h"

#include "parser/ast/Statement.h"
#include "parser/ast/ReturnStatement.h"
#include "parser/ast/ArrayAssignmentStatement.h"

#include "lib/UserDefineFunction.h"

#include "parser/ast/FunctionalExpression.h"

#include "parser/ast/AssignmentStatement.h"
#include "parser/ast/PrintStatement.h"
#include "parser/ast/IfStatement.h"
#include "parser/ast/BlockStatement.h"
#include "parser/ast/BreakStatement.h"
#include "parser/ast/ContinueStatement.h"
#include "parser/ast/DoWhileStatement.h"
#include "parser/ast/WhileStatement.h"
#include "parser/ast/ForStatement.h"
#include "parser/ast/FunctionStatement.h"
#include "parser/ast/FunctionDefine.h"
#include "parser/ast/ReturnStatement.h"

#include "parser/Parser.cpp"

#endif