//
//  visitors/visitor.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__visitor_h
#define visitors__visitor_h

#include "../declaration.h"

class Visitor {
public:
	virtual void visit(ArrayAccessExpression*) = 0;
	virtual void visit(ArrayExpression*) = 0;
	virtual void visit(AssignmentExpression*) = 0;
	virtual void visit(BinaryExpression*) = 0;
	virtual void visit(ConditionalExpression*) = 0;
	virtual void visit(ContainerAccessExpression*) = 0;
	virtual void visit(FunctionalExpression*) = 0;
	virtual void visit(InExpression*) = 0;
	virtual void visit(MapExpression*) = 0;
	virtual void visit(MatchExpression*) = 0;
	virtual void visit(TernaryExpression*) = 0;
	virtual void visit(UnaryExpression*) = 0;
	virtual void visit(ValueExpression*) = 0;
	virtual void visit(VariableExpression*) = 0;

	virtual void visit(ArrayAssignmentStatement*) = 0;
	virtual void visit(BlockStatement*) = 0;
	virtual void visit(BreakStatement*) = 0;
	virtual void visit(ContinueStatement*) = 0;
	virtual void visit(DoWhileStatement*) = 0;
	virtual void visit(ExprStatement*) = 0;
	virtual void visit(ForStatement*) = 0;
	virtual void visit(ForeachStatement*) = 0;
	virtual void visit(FunctionDefineStatement*) = 0;
	virtual void visit(IfStatement*) = 0;
	virtual void visit(IncludeStatement*) = 0;
	virtual void visit(MultiAssignmentStatement*) = 0;
	virtual void visit(PrintStatement*) = 0;
	virtual void visit(PutStatement*) = 0;
	virtual void visit(ReturnStatement*) = 0;
	virtual void visit(UseStatement*) = 0;
	virtual void visit(WhileStatement*) = 0;
};

#endif /* visitors__visitor_h */

