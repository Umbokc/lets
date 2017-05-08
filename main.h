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


class Expression;
class Statement;

class ArrayAccessExpression;
class ArrayAssignmentStatement;
class ArrayExpression;
class AssignmentStatement;
class BinaryExpression;
class BlockStatement;
class BreakStatement;
class ConditionalExpression;
class ContinueStatement;
class DoWhileStatement;
class ForStatement;
class FunctionDefineStatement;
class FunctionStatement;
class FunctionalExpression;
class IfStatement;
class PrintStatement;
class ReturnStatement;
class UnaryExpression;
class ValueExpression;
class VariableExpression;
class WhileStatement;

// не трогать, а то пздц

#include "dop_func.h"

#include "lib/LibClasses.h"

#include "parser/visitors/Visitor.h"

#include "parser/ast/Expression.h"
#include "parser/ast/Statement.h"

#include "lib/UserDefineFunction.h"

#include "parser/ast/ReturnStatement.h"
#include "parser/ast/ArrayAssignmentStatement.h"
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
#include "parser/ast/FunctionDefineStatement.h"
#include "parser/ast/ReturnStatement.h"

#include "parser/ast/ValueExpression.h"
#include "parser/ast/BinaryExpression.h"
#include "parser/ast/UnaryExpression.h"
#include "parser/ast/VariableExpression.h"
#include "parser/ast/ConditionalExpression.h"
#include "parser/ast/ArrayAccessExpression.h"
#include "parser/ast/ArrayExpression.h"
#include "parser/ast/FunctionalExpression.h"

#include "parser/TokenType.h"
#include "parser/Token.h"
#include "parser/Lexer.h"

#include "parser/ast/Expression.h"
#include "parser/ast/Statement.h"

#include "parser/visitors/AbstractVisitor.h"
#include "parser/visitors/FunctionAdder.h"
#include "parser/visitors/VariablesPrint.h"
#include "parser/visitors/AssignValidator.h"

#include "parser/Parser.h"

#endif