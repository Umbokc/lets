#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

class AbstractVisitor : public Visitor{
public:

	void visit(ArrayAccessExpression *s){
		for(auto index: s->indices){
			index->accept(this);
		}
	}

	void visit(ArrayAssignmentStatement *s){
		s->array->accept(this);
		s->expression->accept(this);
	}

	void visit(ArrayExpression *s){
		for(auto index: s->elements){
			index->accept(this);
		}
	}

	void visit(AssignmentStatement *s){
		s->expression->accept(this);
	}

	void visit(BinaryExpression *s){
		s->expr1->accept(this);
		s->expr2->accept(this);
	}

	void visit(BlockStatement *s){
		for(Statement* statement: s->statements){
			statement->accept(this);
		}
	}

	void visit(BreakStatement *s){

	}

	void visit(ConditionalExpression *s){
		s->expr1->accept(this);
		s->expr2->accept(this);
	}

	void visit(ContinueStatement *s){

	}

	void visit(DoWhileStatement *s){
		s->condition->accept(this);
		s->statement->accept(this);
	}

	void visit(ForStatement *s){
		s->initialization->accept(this);
		s->termination->accept(this);
		s->increment->accept(this);
		s->statement->accept(this);
	}

	void visit(FunctionDefineStatement *s){
		s->body->accept(this);
	}

	void visit(FunctionStatement *s){
		s->function->accept(this);
	}

	void visit(FunctionalExpression *s){
		for(Expression* expression: s->arguments){
			expression->accept(this);
		}
	}

	void visit(IfStatement *s){
		s->expression->accept(this);
		s->ifStatement->accept(this);
		if(s->elseStatement != NULL)
			s->elseStatement->accept(this);
	}

	void visit(PrintStatement *s){
		s->expression->accept(this);
	}

	void visit(ReturnStatement *s){
		s->expression->accept(this);
	}

	void visit(UnaryExpression *s){
		s->expr1->accept(this);
	}

	void visit(TernaryExpression *s){
		s->condition->accept(this);
		s->trueExpr->accept(this);
		s->falseExpr->accept(this);
	}

	void visit(ValueExpression *s){

	}

	void visit(VariableExpression *s){
	}

	void visit(WhileStatement *s){
		s->condition->accept(this);
		s->statement->accept(this);
	}

};
#endif