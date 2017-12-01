//
//  visitors/optimization_visitor.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__optimization_visitor_h
#define visitors__optimization_visitor_h

#include <iostream> // for dbg
#include "result_visitor.h"
#include "visitor_utils.h"
#include "../include_ast.h"
#include "../l_user_define_function.hpp"

#define LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(NAME, PARENT) \
	if(NAME* it = dynamic_cast<NAME*>(s)) return this->visit(it, t);

template<class T>
class OptimizationVisitor : virtual public ResultVisitor<Node*, T>{
public:

	virtual Node *visit(ArrayAccessExpression *s, T& t) {
		lets_vector_t<Expression*> indices;
		indices.reserve(s->indices.size());
		bool changed = false;
		for (Expression* expression : s->indices) {
			Node *node = expression->accept(this, t);
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

	virtual Node *visit(ArrayExpression *s, T& t) {
		lets_vector_t<Expression*> elements;
		elements.reserve(s->elements.size());
		bool changed = false;
		for (Expression* expression : s->elements) {
			Node *node = expression->accept(this, t);
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

	virtual Node *visit(AssignmentExpression *s, T& t) {
		Node *exprNode = s->expression->accept(this, t);
		Node *targetNode = s->target->accept(this, t);
		if ( (exprNode != s->expression || targetNode != s->target) && dynamic_cast<Accessible*>(targetNode) ) {
			return new AssignmentExpression(
				s->operation,
				dynamic_cast<Accessible*>(targetNode),
				dynamic_cast<Expression*>(exprNode)
			);
		}
		return s;
	}

	virtual Node *visit(BinaryExpression *s, T& t) {
		Node *expr1 = s->expr1->accept(this, t);
		Node *expr2 = s->expr2->accept(this, t);
		if (expr1 != s->expr1 || expr2 != s->expr2) {
			return new BinaryExpression(s->operation, dynamic_cast<Expression*>(expr1), dynamic_cast<Expression*>(expr2));
		}
		return s;
	}

	virtual Node *visit(ConditionalExpression *s, T& t) {
		Node *expr1 = s->expr1->accept(this, t);
		Node *expr2 = s->expr2->accept(this, t);
		if (expr1 != s->expr1 || expr2 != s->expr2) {
			return new ConditionalExpression(s->operation, dynamic_cast<Expression*>(expr1), dynamic_cast<Expression*>(expr2));
		}
		return s;
	}

	virtual Node *visit(ContainerAccessExpression *s, T& t) {
		Node *root = s->root->accept(this, t);
		bool changed = (root != s->root);

		lets_vector_t<Expression*> indices;
		indices.reserve(s->indices.size());

		for (Expression *expression : s->indices) {
			Node *node = expression->accept(this, t);
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

	virtual Node *visit(FunctionalExpression *s, T& t) {
		
		Node *function_expr = s->function_expr->accept(this, t);
		FunctionalExpression *result = new FunctionalExpression(dynamic_cast<Expression*>(function_expr));
		bool changed = function_expr != s->function_expr;

		for (Expression *argument : s->arguments) {
			Node *expr = argument->accept(this, t);
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

	virtual Node *visit(MapExpression *s, T& t) {
		lets_map_t<Expression*, Expression*> elements;

		bool changed = false;
		for (auto& entry : s->elements) {
			Node *key = entry.first->accept(this, t);
			Node *value = entry.second->accept(this, t);
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

	virtual Node *visit(MatchExpression *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		bool changed = expression != s->expression;
		lets_vector_t<MatchExpression::Pattern*> patterns;
		for (MatchExpression::Pattern *pattern : s->patterns) {
			if (MatchExpression::VariablePattern *tp = dynamic_cast<MatchExpression::VariablePattern*>(pattern)) {
				lets_str_t variable = tp->variable;
				VariableExpression *expr = new VariableExpression(variable);
				Node *node = expr->accept(this, t);
				if (node != expr) {
					if (VisitorUtils::is_value(node)) {
						changed = true;
						Value *value = dynamic_cast<ValueExpression*>(node)->value;
						Expression *opt_condition = pattern->opt_condition;
						Statement *result = pattern->result;
						pattern = new MatchExpression::ConstantPattern(value);
						pattern->opt_condition = opt_condition;
						pattern->result = result;
					}
				}
			}

			if (MatchExpression::TuplePattern *tuple = dynamic_cast<MatchExpression::TuplePattern*>(pattern)) {
				lets_vector_t<Expression*> new_values;
				bool values_changed = false;
				for (Expression *value : tuple->values) {
					Node *node = value->accept(this, t);
					if (node != value) {
						values_changed = true;
						value = dynamic_cast<Expression*>(node);
					}
					new_values.push_back(value);
				}
				if (values_changed) {
					changed = true;
					Expression *opt_condition = pattern->opt_condition;
					Statement *result = pattern->result;
					pattern = new MatchExpression::TuplePattern(new_values);
					pattern->opt_condition = opt_condition;
					pattern->result = result;
				}
			}

			Node *pattern_result = pattern->result->accept(this, t);
			if (pattern_result != pattern->result) {
				changed = true;
				pattern->result = consume_statement(pattern_result);
			}

			if (pattern->opt_condition != NULL) {
				Node *opt_cond = pattern->opt_condition->accept(this, t);
				if (opt_cond != pattern->opt_condition) {
					changed = true;
					pattern->opt_condition = dynamic_cast<Expression*>(opt_cond);
				}
			}

			patterns.push_back(pattern);
		}
		if (changed) {
			return new MatchExpression(dynamic_cast<Expression*>(expression), patterns);
		}
		return s;
	}

	virtual Node *visit(TernaryExpression *s, T& t) {
		Node *condition = s->condition->accept(this, t);
		Node *trueExpr = s->trueExpr->accept(this, t);
		Node *falseExpr = s->falseExpr->accept(this, t);
		if (condition != s->condition || trueExpr != s->trueExpr || falseExpr != s->falseExpr) {
			return new TernaryExpression(dynamic_cast<Expression*>(condition), dynamic_cast<Expression*>(trueExpr), dynamic_cast<Expression*>(falseExpr));
		}
		return s;
	}

	virtual Node *visit(UnaryExpression *s, T& t) {
		Node *expr = s->expr->accept(this, t);
		if (expr != s->expr) {
			return new UnaryExpression(s->operation, dynamic_cast<Expression*>(expr));
		}
		return s;
	}

	virtual Node *visit(ValueExpression *s, T& t) {
		if ( (s->value->type() == Types::T_FUNCTION) && dynamic_cast<UserDefineFunction*>(s->value) ) {
			UserDefineFunction *function = dynamic_cast<UserDefineFunction*>(s->value);
			UserDefineFunction *accepted = visit_f(function, t);
			if (accepted != function) {
				return new ValueExpression(accepted);
			}
		}
		return s;
	}

	virtual Node *visit(VariableExpression *s, T& t) {
		return s;
	}

// Statements 

	virtual Node *visit(ArrayAssignmentStatement *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		Node *array = s->array->accept(this, t);
		if (expression != s->expression || array != s->array) {
			return new ArrayAssignmentStatement(
				dynamic_cast<ArrayAccessExpression*>(array), dynamic_cast<Expression*>(expression)
			);
		}
		return s;
	}

	virtual Node *visit(BlockStatement *s, T& t) {
		bool changed = false;
		BlockStatement *result = new BlockStatement();
		for (Statement *statement : s->statements) {
			Node *node = statement->accept(this, t);
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

	virtual Node *visit(BreakStatement *s, T& t) {
		return s;
	}

	virtual Node *visit(ContinueStatement *s, T& t) {
		return s;
	}

	virtual Node *visit(DoWhileStatement *s, T& t) {
		Node *condition = s->condition->accept(this, t);
		Node *statement = s->statement->accept(this, t);
		if (condition != s->condition || statement != s->statement) {
			return new DoWhileStatement(dynamic_cast<Expression*>(condition), consume_statement(statement));
		}
		return s;
	}

	virtual Node *visit(ExprStatement *s, T& t) {
		Node *expr = s->expr->accept(this, t);
		if (expr != s->expr) {
			return new ExprStatement(dynamic_cast<Expression*>(expr));
		}
		return s;
	}

	virtual Node *visit(ForStatement *s, T& t) {
		Node *initialization = s->initialization->accept(this, t);
		Node *termination = s->termination->accept(this, t);
		Node *increment = s->increment->accept(this, t);
		Node *statement = s->statement->accept(this, t);
		if (initialization != s->initialization || termination != s->termination
			|| increment != s->increment || statement != s->statement) {
			return new ForStatement(
				consume_statement(initialization),
				dynamic_cast<Expression*>(termination), consume_statement(increment), consume_statement(statement)
			);
		}
		return s;
	}

	virtual Node *visit(ForeachStatement *s, T& t) {
		Node *container = s->container->accept(this, t);
		Node *body = s->body->accept(this, t);
		if (container != s->container || body != s->body) {
			return new ForeachStatement(s->key, s->val, dynamic_cast<Expression*>(container), consume_statement(body));
		}
		return s;
	}

	virtual Node *visit(FunctionDefineStatement *s, T& t){
		Arguments newArgs = Arguments();
		bool changed = visit_t(s->args, newArgs, t);

		Node *body = s->body->accept(this, t);
		if (changed || body != s->body) {
			return new FunctionDefineStatement(s->name, newArgs, consume_statement(body));
		}
		return s;
	}

	virtual Node *visit(IfStatement *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		Node *if_statement = s->if_statement->accept(this, t);
		Node *else_statement = (s->else_statement != NULL) ? s->else_statement->accept(this, t) : NULL;

		if (expression != s->expression || if_statement != s->if_statement || else_statement != s->else_statement) {
			return new IfStatement(
				dynamic_cast<Expression*>(expression),
				consume_statement(if_statement), (else_statement == NULL ? NULL : consume_statement(else_statement))
			);
		}

		return s;
	}

	virtual Node *visit(MultiAssignmentStatement *s, T& t) {

		bool changed = false;
		lets_vector_t<Accessible*> targets;
		Node *expression = s->expression->accept(this, t);

		for (Accessible *item : s->targets) {
			if(item != NULL){
				Node *node = item->accept(this, t);
				if (node != item) {
					changed = true;
				}
				if(Accessible* new_node = dynamic_cast<Accessible*>(node)){
					targets.push_back(new_node);
				}
			}
		}

		if(expression != s->expression){
			changed = true;
		}

		if (changed) {
			return new MultiAssignmentStatement(targets, dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	virtual Node *visit(PrintStatement *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		if (expression != s->expression) {
			return new PrintStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	virtual Node *visit(PutStatement *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		if (expression != s->expression) {
			return new PutStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	virtual Node *visit(ReturnStatement *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		if (expression != s->expression) {
			return new ReturnStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	virtual Node *visit(UseStatement *s, T& t) {
		Node *expression = s->expression->accept(this, t);
		if(ArrayExpression* ae = dynamic_cast<ArrayExpression*>(s->elements)){
			Node *elements = ae->accept(this, t);
			if (expression != NULL || elements != NULL)
				if (expression != s->expression || elements != s->elements)
					if(dynamic_cast<Expression*>(expression) and dynamic_cast<Expression*>(elements))
						return new UseStatement(dynamic_cast<Expression*>(expression), dynamic_cast<Expression*>(elements));
		}
		return s;
	}

	virtual Node *visit(WhileStatement *s, T& t) {
		Node *condition = s->condition->accept(this, t);
		Node *statement = s->statement->accept(this, t);
		if (condition != s->condition || statement != s->statement) {
			return new WhileStatement(dynamic_cast<Expression*>(condition), consume_statement(statement));
		}
		return s;
	}

	// virtual Node *visit(SelfStatement *s, T& t) {
	// 	return s;
	// }

	// virtual Node *visit(ModeProgrammStatement *s, T& t) {
	// 	return s;
	// }

	UserDefineFunction *visit_f(UserDefineFunction *s, T& t){
		
		Arguments newArgs = Arguments();
		bool changed = visit_t(s->args, newArgs, t);
		Node *body = s->body->accept(this, t);

		if (changed || body != s->body) {
			return new UserDefineFunction(newArgs, consume_statement(body));
		}
		return s;
	}

	virtual Node *visit(Node *s, T& t) {

		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ArrayAssignmentStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(BlockStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(BreakStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ContinueStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(DoWhileStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ExprStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ForStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ForeachStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(FunctionDefineStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(IfStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(MultiAssignmentStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(PrintStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(PutStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ReturnStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(UseStatement, Statement)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(WhileStatement, Statement)

		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ArrayAccessExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ArrayExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(AssignmentExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(BinaryExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ConditionalExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ContainerAccessExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(FunctionalExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(MapExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(MatchExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(TernaryExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(UnaryExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(ValueExpression, Expression)
		LETS_CALL_VISIT_ACCEPT_IF_IT_IS_STAT_OR_EXPR(VariableExpression, Expression)

		return s;
	}

protected:
	bool visit_t(Arguments in, Arguments out, T& t){
		bool changed = false;
		for (int i = 0; i < in.get_size(); ++i) {
			Argument argument = in.get(i);
			Expression *valueExpr = argument.get_value_expr();
			if (valueExpr == NULL) {
				out.add_required(argument.get_name());
			} else {
				Node *expr = valueExpr->accept(this, t);
				if (expr != valueExpr) {
					changed = true;
				}
				out.add_optional(argument.get_name(), dynamic_cast<Expression*>(expr));
			}

		}
		return changed;
	}

private:
	Statement* consume_statement(Node *node) {
		if (dynamic_cast<Statement*>(node)) {
			return dynamic_cast<Statement*>(node);
		}
		return new ExprStatement(dynamic_cast<Expression*>(node));
	}
};

#endif /* visitors__optimization_visitor_h */

