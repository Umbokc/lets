#ifndef VISITOR_H
#define VISITOR_H

class Visitor {
public:
	virtual void visit(ArrayAccessExpression *s) = 0;
	virtual void visit(ArrayAssignmentStatement *s) = 0;
	virtual void visit(ArrayExpression *s) = 0;
	virtual void visit(AssignmentStatement *s) = 0;
	virtual void visit(BinaryExpression *s) = 0;
	virtual void visit(BlockStatement *s) = 0;
	virtual void visit(BreakStatement *s) = 0;
	virtual void visit(ConditionalExpression *s) = 0;
	virtual void visit(ContinueStatement *s) = 0;
	virtual void visit(DoWhileStatement *s) = 0;
	virtual void visit(ForStatement *s) = 0;
	virtual void visit(FunctionDefineStatement *s) = 0;
	virtual void visit(FunctionStatement *s) = 0;
	virtual void visit(FunctionalExpression *s) = 0;
	virtual void visit(IfStatement *s) = 0;
	virtual void visit(PrintStatement *s) = 0;
	virtual void visit(ReturnStatement *s) = 0;
	virtual void visit(UnaryExpression *s) = 0;
	virtual void visit(ValueExpression *s) = 0;
	virtual void visit(VariableExpression *s) = 0;
	virtual void visit(WhileStatement *s) = 0;
};

class Node {
public:
	virtual void accept(Visitor *visitor) = 0;
};

#endif