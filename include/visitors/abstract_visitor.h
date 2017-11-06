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
		for(auto index: s->indices){
			index->accept(index, this);
		}
	}

	void visit(ArrayExpression *s){
		for(auto index: s->elements){
			index->accept(index, this);
		}
	}

	void visit(AssignmentExpression *s){
		s->target->accept(s->target,this);
		s->expression->accept(s->expression,this);
	}

	void visit(BinaryExpression *s){
		s->expr1->accept(s->expr1, this);
		s->expr2->accept(s->expr2, this);
	}

	void visit(ConditionalExpression *s){
		s->expr1->accept(s->expr1, this);
		s->expr2->accept(s->expr2, this);
	}

	void visit(ContainerAccessExpression *s){
		s->root->accept(s->root, this);
		int size = s->indices.size();
		for(int i = 0; i < size; i++){
			s->indices[i]->accept(s->indices[i], this);
		}
	}

	void visit(FunctionalExpression *s){
		for(Expression* expression: s->arguments){
			expression->accept(expression, this);
		}
	}

	void visit(MapExpression *s){
		for (auto& elem : s->elements){
			elem.first->accept(elem.first, this);
			elem.second->accept(elem.second, this);
		}
	}

	void visit(MatchExpression *s){

	}

	void visit(TernaryExpression *s){
		s->condition->accept(s->condition, this);
		s->trueExpr->accept(s->trueExpr, this);
		s->falseExpr->accept(s->falseExpr, this);
	}

	void visit(UnaryExpression *s){
		s->expr->accept(s->expr,this);
	}

	void visit(ValueExpression *s){

	}

	void visit(VariableExpression *s){

	}

// Statements

	void visit(ArrayAssignmentStatement *s){
		s->array->accept(s->array,this);
		s->expression->accept(s->expression,this);
	}

	void visit(AssignmentStatement *s){
		s->expression->accept(s->expression,this);
	}

	void visit(BlockStatement *s){
		for(Statement* statement: s->statements){
			statement->accept(statement,this);
		}
	}

	void visit(BreakStatement *s){

	}

	void visit(ContinueStatement *s){

	}

	void visit(DoWhileStatement *s){
		s->condition->accept(s->condition,this);
		s->statement->accept(s->statement,this);
	}

	void visit(ExprStatement *s){
		s->expr->accept(s->expr,this);
	}

	void visit(ForStatement *s){
		s->initialization->accept(s->initialization,this);
		s->termination->accept(s->termination,this);
		s->increment->accept(s->increment,this);
		s->statement->accept(s->statement,this);
	}

	void visit(ForeachStatement *s){
		s->container->accept(s->container,this);
		s->body->accept(s->body,this);
	}

	void visit(FunctionDefineStatement *s){
		s->body->accept(s->body,this);
	}

	void visit(IfStatement *s){
		s->expression->accept(s->expression,this);
		s->if_statement->accept(s->if_statement,this);
		if(s->else_statement != NULL)
			s->else_statement->accept(s->else_statement,this);
	}

	void visit(PrintStatement *s){
		s->expression->accept(s->expression,this);
	}
	
	void visit(PutStatement *s){
		s->expression->accept(s->expression,this);
	}

	void visit(ReturnStatement *s){
		s->expression->accept(s->expression,this);
	}

	void visit(UseStatement *s){
		s->expression->accept(s->expression, this);
		s->elements->accept(s->elements, this);
	}

	void visit(WhileStatement *s){
		s->condition->accept(s->condition,this);
		s->statement->accept(s->statement,this);
	}

	void visit(Node* item){
		if(Statement* it = dynamic_cast<Statement*>(item)){
			visit(it);
		}
		if(Expression* it = dynamic_cast<Expression*>(item)){
			visit(it);
		}
	}

	void visit(Statement* item){
		if(ArrayAssignmentStatement* it = dynamic_cast<ArrayAssignmentStatement*>(item)) it->accept(it, this);
		if(AssignmentStatement* it = dynamic_cast<AssignmentStatement*>(item)) it->accept(it, this);
		if(BlockStatement* it = dynamic_cast<BlockStatement*>(item)) it->accept(it, this);
		if(BreakStatement* it = dynamic_cast<BreakStatement*>(item)) it->accept(it, this);
		if(ContinueStatement* it = dynamic_cast<ContinueStatement*>(item)) it->accept(it, this);
		if(DoWhileStatement* it = dynamic_cast<DoWhileStatement*>(item)) it->accept(it, this);
		if(ExprStatement* it = dynamic_cast<ExprStatement*>(item)) it->accept(it, this);
		if(ForStatement* it = dynamic_cast<ForStatement*>(item)) it->accept(it, this);
		if(ForeachStatement* it = dynamic_cast<ForeachStatement*>(item)) it->accept(it, this);
		if(FunctionDefineStatement* it = dynamic_cast<FunctionDefineStatement*>(item)) it->accept(it, this);
		if(IfStatement* it = dynamic_cast<IfStatement*>(item)) it->accept(it, this);
		if(PrintStatement* it = dynamic_cast<PrintStatement*>(item)) it->accept(it, this);
		if(PutStatement* it = dynamic_cast<PutStatement*>(item)) it->accept(it, this);
		if(ReturnStatement* it = dynamic_cast<ReturnStatement*>(item)) it->accept(it, this);
		if(UseStatement* it = dynamic_cast<UseStatement*>(item)) it->accept(it, this);
		if(WhileStatement* it = dynamic_cast<WhileStatement*>(item)) it->accept(it, this);
	}

	void visit(Expression* item){
		if(ArrayAccessExpression* it = dynamic_cast<ArrayAccessExpression*>(item)) it->accept(it, this);
		if(ArrayExpression* it = dynamic_cast<ArrayExpression*>(item)) it->accept(it, this);
		if(AssignmentExpression* it = dynamic_cast<AssignmentExpression*>(item)) it->accept(it, this);
		if(BinaryExpression* it = dynamic_cast<BinaryExpression*>(item)) it->accept(it, this);
		if(ConditionalExpression* it = dynamic_cast<ConditionalExpression*>(item)) it->accept(it, this);
		if(ContainerAccessExpression* it = dynamic_cast<ContainerAccessExpression*>(item)) it->accept(it, this);
		if(FunctionalExpression* it = dynamic_cast<FunctionalExpression*>(item)) it->accept(it, this);
		if(MapExpression* it = dynamic_cast<MapExpression*>(item)) it->accept(it, this);
		if(MatchExpression* it = dynamic_cast<MatchExpression*>(item)) it->accept(it, this);
		if(TernaryExpression* it = dynamic_cast<TernaryExpression*>(item)) it->accept(it, this);
		if(UnaryExpression* it = dynamic_cast<UnaryExpression*>(item)) it->accept(it, this);
		if(ValueExpression* it = dynamic_cast<ValueExpression*>(item)) it->accept(it, this);
		if(VariableExpression* it = dynamic_cast<VariableExpression*>(item)) it->accept(it, this);
	}
};

#endif /* visitors__abstract_visitor_h */

