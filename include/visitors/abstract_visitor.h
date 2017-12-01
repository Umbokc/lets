//
//  visitors/abstract_visitor.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__abstract_visitor_h
#define visitors__abstract_visitor_h

#include "visitor.h"
#include "../include_ast.h"

class AbstractVisitor : virtual public Visitor{
public:

// Expressions

	void visit(ArrayAccessExpression *s){
		for(Expression* index: s->indices){
			index->accept(this);
		}
	}

	void visit(ArrayExpression *s){
		for(Expression* index: s->elements){
			index->accept(this);
		}
	}

	void visit(AssignmentExpression *s){
		s->target->accept(this);
		s->expression->accept(this);
	}

	void visit(BinaryExpression *s){
		s->expr1->accept(this);
		s->expr2->accept(this);
	}

	void visit(ConditionalExpression *s){
		s->expr1->accept(this);
		s->expr2->accept(this);
	}

	void visit(ContainerAccessExpression *s){
		s->root->accept(this);
		int size = s->indices.size();
		for(int i = 0; i < size; i++){
			s->indices[i]->accept(this);
		}
	}

	void visit(FunctionalExpression *s){
		for(Expression* expression: s->arguments){
			expression->accept(this);
		}
	}

	void visit(InExpression *s){
		for(Expression* expression: s->expressions){
			expression->accept(this);
		}
		s->container->accept(this);
	}

	void visit(MapExpression *s){
		for (auto& elem : s->elements){
			elem.first->accept(this);
			elem.second->accept(this);
		}
	}

	void visit(MatchExpression *s){

	}

	void visit(TernaryExpression *s){
		s->condition->accept(this);
		s->trueExpr->accept(this);
		s->falseExpr->accept(this);
	}

	void visit(UnaryExpression *s){
		s->expr->accept(this);
	}

	void visit(ValueExpression *s){

	}

	void visit(VariableExpression *s){

	}

// Statements

	void visit(ArrayAssignmentStatement *s){
		s->array->accept(this);
		s->expression->accept(this);
	}

	void visit(BlockStatement *s){
		for(Statement* statement: s->statements){
			statement->accept(this);
		}
	}

	void visit(BreakStatement *s){

	}

	void visit(ContinueStatement *s){

	}

	void visit(DoWhileStatement *s){
		s->condition->accept(this);
		s->statement->accept(this);
	}

	void visit(ExprStatement *s){
		s->expr->accept(this);
	}

	void visit(ForStatement *s){
		s->initialization->accept(this);
		s->termination->accept(this);
		s->increment->accept(this);
		s->statement->accept(this);
	}

	void visit(ForeachStatement *s){
		s->container->accept(this);
		s->body->accept(this);
	}

	void visit(FunctionDefineStatement *s){
		s->body->accept(this);
	}

	void visit(IfStatement *s){
		s->expression->accept(this);
		s->if_statement->accept(this);
		if(s->else_statement != NULL)
			s->else_statement->accept(this);
	}

	void visit(IncludeStatement *s){
		s->expression->accept(this);
	}

	void visit(MultiAssignmentStatement *s){
		s->expression->accept(this);
		for(Accessible* item: s->targets){
			item->accept(this);
		}
	}

	void visit(PrintStatement *s){
		s->expression->accept(this);
	}
	
	void visit(PutStatement *s){
		s->expression->accept(this);
	}

	void visit(ReturnStatement *s){
		s->expression->accept(this);
	}

	void visit(UseStatement *s){
		s->expression->accept(this);
		s->elements->accept(this);
	}

	void visit(WhileStatement *s){
		s->condition->accept(this);
		s->statement->accept(this);
	}

};

#endif /* visitors__abstract_visitor_h */

