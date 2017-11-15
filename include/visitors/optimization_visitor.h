//
//  visitors/optimization_visitor.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__optimization_visitor_h
#define visitors__optimization_visitor_h

#include "result_visitor.h"
#include "../include_ast.h"
#include "../l_user_define_function.hpp"

template<class T>
class OptimizationVisitor : public ResultVisitor<Node*, T>{
public:

	Node *visit(ArrayAccessExpression *s, T t) {
		lets_vector_t<Expression*> indices;
		indices.reserve(s->indices.size());
		bool changed = false;
		for (Expression* expression : s->indices) {
			Node *node = expression->accept(expression, this, t);
			if (node != expression) {
				changed = true;
			}
			indices.push_back(dynamic_cast<Expression*>(node));
		}
		if (changed) {
			return new ArrayExpression(indices);
		}
		return s;
	}

	Node *visit(ArrayExpression *s, T t) {
		lets_vector_t<Expression*> elements;
		elements.reserve(s->elements.size());
		bool changed = false;
		for (Expression* expression : s->elements) {
			Node *node = expression->accept(expression, this, t);
			if (node != expression) {
				changed = true;
			}
			elements.push_back(dynamic_cast<Expression*>(node));
		}
		if (changed) {
			return new ArrayExpression(elements);
		}
		return s;
	}

	Node *visit(AssignmentExpression *s, T t) {
		Node *exprNode = s->expression->accept(s->expression, this, t);
		Node *targetNode = s->target->accept(s->target, this, t);
		if ( (exprNode != s->expression || targetNode != s->target) && dynamic_cast<Accessible*>(targetNode) ) {
			return new AssignmentExpression(
				s->operation,
				dynamic_cast<Accessible*>(targetNode),
				dynamic_cast<Expression*>(exprNode)
			);
		}
		return s;
	}

	Node *visit(BinaryExpression *s, T t) {
		Node *expr1 = s->expr1->accept(s->expr1, this, t);
		Node *expr2 = s->expr2->accept(s->expr2, this, t);
		if (expr1 != s->expr1 || expr2 != s->expr2) {
			return new BinaryExpression(s->operation, dynamic_cast<Expression*>(expr1), dynamic_cast<Expression*>(expr2));
		}
		return s;
	}

	Node *visit(ConditionalExpression *s, T t) {
		Node *expr1 = s->expr1->accept(s->expr1, this, t);
		Node *expr2 = s->expr2->accept(s->expr2, this, t);
		if (expr1 != s->expr1 || expr2 != s->expr2) {
			return new ConditionalExpression(s->operation, dynamic_cast<Expression*>(expr1), dynamic_cast<Expression*>(expr2));
		}
		return s;
	}

	Node *visit(ContainerAccessExpression *s, T t) {
		Node *root = s->root->accept(s->root, this, t);
		bool changed = (root != s->root);

		lets_vector_t<Expression*> indices;
		indices.reserve(s->indices.size());

		for (Expression *expression : s->indices) {
			Node *node = expression->accept(expression, this, t);
			if (node != expression) {
				changed = true;
			}
			indices.push_back(dynamic_cast<Expression*>(node));
		}
		if (changed) {
			return new ContainerAccessExpression(dynamic_cast<Expression*>(root), indices);
		}
		return s;
	}

	Node *visit(FunctionalExpression *s, T t) {
		
		Node *function_expr = s->function_expr->accept(s->function_expr, this, t);
		FunctionalExpression *result = new FunctionalExpression(dynamic_cast<Expression*>(function_expr));
		bool changed = function_expr != s->function_expr;

		for (Expression *argument : s->arguments) {
			Node *expr = argument->accept(argument, this, t);
			if (expr != argument) {
				changed = true;
			}
			result->add_arguments(dynamic_cast<Expression*>(expr));
		}
		if (changed) {
			return result;
		}
		return s;
	}

	Node *visit(MapExpression *s, T t) {
		lets_map_t<Expression*, Expression*> elements;

		bool changed = false;
		for (auto& entry : s->elements) {
			Node *key = entry.first->accept(entry.first, this, t);
			Node *value = entry.second->accept(entry.second, this, t);
			if (key != entry.first || value != entry.second) {
				changed = true;
			}
			elements[dynamic_cast<Expression*>(key)] = dynamic_cast<Expression*>(value);
		}
		if (changed) {
			return new MapExpression(elements);
		}
		return s;
	}

	Node *visit(MatchExpression *s, T t) {
		return s;
	}

	Node *visit(TernaryExpression *s, T t) {
		Node *condition = s->condition->accept(s->condition, this, t);
		Node *trueExpr = s->trueExpr->accept(s->trueExpr, this, t);
		Node *falseExpr = s->falseExpr->accept(s->falseExpr, this, t);
		if (condition != s->condition || trueExpr != s->trueExpr || falseExpr != s->falseExpr) {
			return new TernaryExpression(dynamic_cast<Expression*>(condition), dynamic_cast<Expression*>(trueExpr), dynamic_cast<Expression*>(falseExpr));
		}
		return s;
	}

	Node *visit(UnaryExpression *s, T t) {
		Node *expr = s->expr->accept(s->expr, this, t);
		if (expr != s->expr) {
			return new UnaryExpression(s->operation, dynamic_cast<Expression*>(expr));
		}
		return s;
	}

	Node *visit(ValueExpression *s, T t) {
		if ( (s->value->type() == Types::T_FUNCTION) && dynamic_cast<UserDefineFunction*>(s->value) ) {
			UserDefineFunction *function = dynamic_cast<UserDefineFunction*>(s->value);
			UserDefineFunction *accepted = visit_f(function, t);
			if (accepted != function) {
				return new ValueExpression(accepted);
			}
		}
		return s;
	}

	Node *visit(VariableExpression *s, T t) {
		return s;
	}

// Statements 

	Node *visit(ArrayAssignmentStatement *s, T t) {
		Node *expression = s->expression->accept(s->expression, this, t);
		Node *array = s->array->accept(s->array, this, t);
		if (expression != s->expression || array != s->array) {
			return new ArrayAssignmentStatement(
				dynamic_cast<ArrayAccessExpression*>(array), dynamic_cast<Expression*>(expression)
			);
		}
		return s;
	}

	Node *visit(BlockStatement *s, T t) {
		bool changed = false;
		BlockStatement *result = new BlockStatement();
		for (Statement *statement : s->statements) {
			Node *node = statement->accept(statement, this, t);
			if (node != statement) {
				changed = true;
			}
			if (dynamic_cast<Statement*>(node)) {
				result->add(dynamic_cast<Statement*>(node));
			} else if (dynamic_cast<Expression*>(node)) {
				result->add(new ExprStatement(dynamic_cast<Expression*>(node)));
			}
		}
		if (changed) {
			return result;
		}
		return s;
	}

	Node *visit(BreakStatement *s, T t) {
		return s;
	}

	Node *visit(ContinueStatement *s, T t) {
		return s;
	}

	Node *visit(DoWhileStatement *s, T t) {
		Node *condition = s->condition->accept(s->condition, this, t);
		Node *statement = s->statement->accept(s->statement, this, t);
		if (condition != s->condition || statement != s->statement) {
			return new DoWhileStatement(dynamic_cast<Expression*>(condition), consumeStatement(statement));
		}
		return s;
	}

	Node *visit(ExprStatement *s, T t) {
		Node *expr = s->expr->accept(s->expr, this, t);
		if (expr != s->expr) {
			return new ExprStatement(dynamic_cast<Expression*>(expr));
		}
		return s;
	}

	Node *visit(ForStatement *s, T t) {
		Node *initialization = s->initialization->accept(s->initialization, this, t);
		Node *termination = s->termination->accept(s->termination, this, t);
		Node *increment = s->increment->accept(s->increment, this, t);
		Node *statement = s->statement->accept(s->statement, this, t);
		if (initialization != s->initialization || termination != s->termination
			|| increment != s->increment || statement != s->statement) {
			return new ForStatement(
				consumeStatement(initialization),
				dynamic_cast<Expression*>(termination), consumeStatement(increment), consumeStatement(statement)
			);
		}
		return s;
	}

	Node *visit(ForeachStatement *s, T t) {
		Node *container = s->container->accept(s->container, this, t);
		Node *body = s->body->accept(s->body, this, t);
		if (container != s->container || body != s->body) {
			return new ForeachStatement(s->key, s->val, dynamic_cast<Expression*>(container), consumeStatement(body));
		}
		return s;
	}

	Node *visit(FunctionDefineStatement *s, T t){
		Arguments newArgs = Arguments();
		bool changed = visit_t(s->args, newArgs, t);

		Node *body = s->body->accept(s->body, this, t);
		if (changed || body != s->body) {
			return new FunctionDefineStatement(s->name, newArgs, consumeStatement(body), s->is_constexpr);
		}
		return s;
	}

	Node *visit(IfStatement *s, T t) {
		Node *expression = s->expression->accept(s->expression, this, t);
		Node *if_statement = s->if_statement->accept(s->if_statement, this, t);
		Node *else_statement = (s->else_statement != NULL) ? s->else_statement->accept(s->else_statement, this, t) : NULL;

		if (expression != s->expression || if_statement != s->if_statement || else_statement != s->else_statement) {
			return new IfStatement(
				dynamic_cast<Expression*>(expression),
				consumeStatement(if_statement), (else_statement == NULL ? NULL : consumeStatement(else_statement))
			);
		}

		return s;
	}

	Node *visit(MultiAssignmentStatement *s, T t) {
		bool changed = false;
		lets_vector_t<Accessible*> targets;
		Node *expression = s->expression->accept(s->expression, this, t);

		for (Accessible *item : s->targets) {
			Node *node = item->accept(item, this, t);
			if (node != item) {
				changed = true;
			}
			targets.push_back(dynamic_cast<Accessible*>(node));
		}

		if(expression != s->expression){
			changed = true;
		}

		if (changed) {
			return new MultiAssignmentStatement(targets, dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(PrintStatement *s, T t) {
		Node *expression = s->expression->accept(s->expression, this, t);
		if (expression != s->expression) {
			return new PrintStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(PutStatement *s, T t) {
		Node *expression = s->expression->accept(s->expression, this, t);
		if (expression != s->expression) {
			return new PutStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(ReturnStatement *s, T t) {
		Node *expression = s->expression->accept(s->expression, this, t);
		if (expression != s->expression) {
			return new ReturnStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(UseStatement *s, T t) {
		Node *expression = s->expression->accept(s->expression, this, t);
		Node *elements = s->elements->accept(s->elements, this, t);
		if (expression != s->expression || elements != s->elements) {
			return new UseStatement(dynamic_cast<Expression*>(expression), dynamic_cast<Expression*>(elements));
		}
		return s;
	}

	Node *visit(WhileStatement *s, T t) {
		Node *condition = s->condition->accept(s->condition, this, t);
		Node *statement = s->statement->accept(s->statement, this, t);
		if (condition != s->condition || statement != s->statement) {
			return new WhileStatement(dynamic_cast<Expression*>(condition), consumeStatement(statement));
		}
		return s;
	}

	// Node *visit(SelfStatement *s, T t) {
	// 	return s;
	// }

	// Node *visit(ModeProgrammStatement *s, T t) {
	// 	return s;
	// }

	UserDefineFunction *visit_f(UserDefineFunction *s, T t){
		
		Arguments newArgs = Arguments();
		bool changed = visit_t(s->args, newArgs, t);
		Node *body = s->body->accept(s->body, this, t);

		if (changed || body != s->body) {
			return new UserDefineFunction(newArgs, consumeStatement(body));
		}
		return s;
	}

	Node *visit(Node *s, T t) {
		if(Statement* it = dynamic_cast<Statement*>(s)){
			s = visit(it, t);
		}
		if(Expression* it = dynamic_cast<Expression*>(s)){
			s = visit(it, t);
		}
		return s;
	}
	
	Node *visit(Statement *s, T t) {

		if(ArrayAssignmentStatement* it = dynamic_cast<ArrayAssignmentStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(BlockStatement* it = dynamic_cast<BlockStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(BreakStatement* it = dynamic_cast<BreakStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(ContinueStatement* it = dynamic_cast<ContinueStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(DoWhileStatement* it = dynamic_cast<DoWhileStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(ExprStatement* it = dynamic_cast<ExprStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(ForStatement* it = dynamic_cast<ForStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(ForeachStatement* it = dynamic_cast<ForeachStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(FunctionDefineStatement* it = dynamic_cast<FunctionDefineStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(IfStatement* it = dynamic_cast<IfStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(MultiAssignmentStatement* it = dynamic_cast<MultiAssignmentStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(PrintStatement* it = dynamic_cast<PrintStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(PutStatement* it = dynamic_cast<PutStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(ReturnStatement* it = dynamic_cast<ReturnStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(UseStatement* it = dynamic_cast<UseStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));
		else if(WhileStatement* it = dynamic_cast<WhileStatement*>(s)) s = dynamic_cast<Statement*>(it->accept(it, this, t));

		return dynamic_cast<Node*>(s);
	}

	Node *visit(Expression *s, T t) {

		if(ArrayAccessExpression* it = dynamic_cast<ArrayAccessExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(ArrayExpression* it = dynamic_cast<ArrayExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(AssignmentExpression* it = dynamic_cast<AssignmentExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(BinaryExpression* it = dynamic_cast<BinaryExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(ConditionalExpression* it = dynamic_cast<ConditionalExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(ContainerAccessExpression* it = dynamic_cast<ContainerAccessExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(FunctionalExpression* it = dynamic_cast<FunctionalExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(MapExpression* it = dynamic_cast<MapExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(MatchExpression* it = dynamic_cast<MatchExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(TernaryExpression* it = dynamic_cast<TernaryExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(UnaryExpression* it = dynamic_cast<UnaryExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(ValueExpression* it = dynamic_cast<ValueExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));
		else if(VariableExpression* it = dynamic_cast<VariableExpression*>(s)) s = dynamic_cast<Expression*>(it->accept(it, this, t));

		return dynamic_cast<Node*>(s);
	}

protected:
	bool visit_t(Arguments in, Arguments out, T t){
		bool changed = false;
		for (int i = 0; i < in.get_size(); ++i) {
			Argument argument = in.get(i);
			Expression *valueExpr = argument.get_value_expr();
			if (valueExpr == NULL) {
				out.add_required(argument.get_name());
			} else {
				Node *expr = valueExpr->accept(valueExpr, this, t);
				if (expr != valueExpr) {
					changed = true;
				}
				out.add_optional(argument.get_name(), dynamic_cast<Expression*>(expr));
			}

		}
		return changed;
	}

private:
	Statement* consumeStatement(Node *node) {
		if (dynamic_cast<Statement*>(node)) {
			return dynamic_cast<Statement*>(node);
		}
		return new ExprStatement(dynamic_cast<Expression*>(node));
	}
};

#endif /* visitors__optimization_visitor_h */

