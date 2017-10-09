#ifndef LL_UTILS_VISITORS_RESULT_VISITOR_H
#define LL_UTILS_VISITORS_RESULT_VISITOR_H

#include "../../include/declaration.h"

template<class R>
class ResultVisitor {
public:
	R visit(ArrayAccessExpression *s);
	R visit(ArrayExpression *s);
	R visit(AssignmentExpression *s);
	R visit(BinaryExpression *s);
	R visit(ConditionalExpression *s);
	R visit(FunctionalExpression *s);
	R visit(MapExpression *s);
	R visit(TernaryExpression *s);
	R visit(ContainerAccessExpression *s);
	R visit(UnaryExpression *s);
	R visit(ValueExpression *s);
	R visit(VariableExpression *s);
	R visit(InputExpression *s);
	R visit(MatchExpression *s);
	
	R visit(ArrayAssignmentStatement *s);
	R visit(AssignmentStatement *s);
	R visit(BlockStatement *s);
	R visit(BreakStatement *s);
	R visit(ContinueStatement *s);
	R visit(DoWhileStatement *s);
	R visit(ForStatement *s);
	R visit(ForeachStatement *s);
	R visit(FunctionDefineStatement *s);
	R visit(ExprStatement *s);
	R visit(IfStatement *s);
	R visit(PrintStatement *s);
	R visit(PutStatement *s);
	R visit(ReturnStatement *s);
	R visit(UseStatement *s);
	R visit(WhileStatement *s);
	R visit(ModeProgrammStatement *s);
	R visit(SelfStatement *s);
};

#endif