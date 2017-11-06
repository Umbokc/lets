//
//  visitors/result_visitor.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__result_visitor_h
#define visitors__result_visitor_h

#include "../declaration.h"

template<class R, class T>
class ResultVisitor {
public:
	virtual R visit(ArrayAccessExpression*, T) = 0;
	virtual R visit(ArrayExpression*, T) = 0;
	virtual R visit(AssignmentExpression*, T) = 0;
	virtual R visit(BinaryExpression*, T) = 0;
	virtual R visit(ConditionalExpression*, T) = 0;
	virtual R visit(ContainerAccessExpression*, T) = 0;
	virtual R visit(FunctionalExpression*, T) = 0;
	virtual R visit(MapExpression*, T) = 0;
	virtual R visit(MatchExpression*, T) = 0;
	virtual R visit(TernaryExpression*, T) = 0;
	virtual R visit(UnaryExpression*, T) = 0;
	virtual R visit(ValueExpression*, T) = 0;
	virtual R visit(VariableExpression*, T) = 0;

	virtual R visit(ArrayAssignmentStatement*, T) = 0;
	virtual R visit(AssignmentStatement*, T) = 0;
	virtual R visit(BlockStatement*, T) = 0;
	virtual R visit(BreakStatement*, T) = 0;
	virtual R visit(ContinueStatement*, T) = 0;
	virtual R visit(DoWhileStatement*, T) = 0;
	virtual R visit(ExprStatement*, T) = 0;
	virtual R visit(ForStatement*, T) = 0;
	virtual R visit(ForeachStatement*, T) = 0;
	virtual R visit(FunctionDefineStatement*, T) = 0;
	virtual R visit(IfStatement*, T) = 0;
	virtual R visit(PrintStatement*, T) = 0;
	virtual R visit(PutStatement*, T) = 0;
	virtual R visit(ReturnStatement*, T) = 0;
	virtual R visit(UseStatement*, T) = 0;
	virtual R visit(WhileStatement*, T) = 0;

	virtual R visit(Node*, T) = 0;
	virtual R visit(Statement*, T) = 0;
	virtual R visit(Expression*, T) = 0;
};

#endif /* visitors__result_visitor_h */

