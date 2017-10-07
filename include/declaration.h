#ifndef DECLARATION_H
#define DECLARATION_H

class Value;

class Visitor;
class Node;
class Expression;
class Accessible;
// class AccessExpr;
class Argument;
class Arguments;
class ArrayAccessExpression;
class ArrayExpression;
class AssignmentExpression;
class BinaryExpression;
class ConditionalExpression;
class FunctionalExpression;
class MapExpression;
class UnaryExpression;
class ContainerAccessExpression;
class TernaryExpression;
class ValueExpression;
class VariableExpression;
class InputExpression;
class MatchExpression;

class Statement;
class ArrayAssignmentStatement;
class AssignmentStatement;
class BlockStatement;
class BreakStatement;
class ContinueStatement;
class DoWhileStatement;
class ForStatement;
class ForeachStatement;
class FunctionDefineStatement;
class ExprStatement;
class IfStatement;
class PrintStatement;
class PutStatement;
class ReturnStatement;
class UseStatement;
class WhileStatement;
class ModeProgrammStatement;
class SelfStatement;

class SelfStatementResponse {
public:
	Value* result;
	SelfStatementResponse(Value * result):result(std::move(result)){
		dbg("SelfStatementResponse");
	}
};

#endif