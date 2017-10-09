#ifndef LL_UTIL_OPTIMIZATION_VISITOR_H
#define LL_UTIL_OPTIMIZATION_VISITOR_H

#include "../../include/declaration.h"
#include "../visitors/result_visitor.h"
#include "../../include/node.h"

class OptimizationVisitor : virtual public ResultVisitor<Node*>{
public:
	Node *visit(ArrayExpression *s) {
		std::vector<Expression*> elements;
		elements.reserve(s->elements.size());
		bool changed = false;
		for (Expression* expression : s->elements) {
			Node *node = expression->accept_r(this);
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

	Node *visit(AssignmentExpression *s) {
		Node *exprNode = s->expression->accept_r(this);
		Node *targetNode = s->target->accept_r(this);
		if ( (exprNode != s->expression || targetNode != s->target) && dynamic_cast<Accessible*>(targetNode) ) {
			return new AssignmentExpression(
				s->operation,
				dynamic_cast<Accessible*>(targetNode),
				dynamic_cast<Expression*>(exprNode)
			);
		}
		return s;
	}

	Node *visit(BinaryExpression *s) {
		Node *expr1 = s->expr1->accept_r(this);
		Node *expr2 = s->expr2->accept_r(this);
		if (expr1 != s->expr1 || expr2 != s->expr2) {
			return new BinaryExpression(s->operation, dynamic_cast<Expression*>(expr1), dynamic_cast<Expression*>(expr2));
		}
		return s;
	}

	Node *visit(BlockStatement *s) {
		bool changed = false;
		BlockStatement *result = new BlockStatement();
		for (Statement *statement : s->statements) {
			Node *node = statement->accept_r(this);
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

	Node *visit(BreakStatement *s) {
		return s;
	}

	Node *visit(ConditionalExpression *s) {
		Node *expr1 = s->expr1->accept_r(this);
		Node *expr2 = s->expr2->accept_r(this);
		if (expr1 != s->expr1 || expr2 != s->expr2) {
			return new ConditionalExpression(s->operation, dynamic_cast<Expression*>(expr1), dynamic_cast<Expression*>(expr2));
		}
		return s;
	}

	Node *visit(ContainerAccessExpression *s) {
		Node *root = s->root->accept_r(this);
		bool changed = (root != s->root);

		std::vector<Expression*> indices;
		indices.reserve(s->indices.size());

		for (Expression *expression : s->indices) {
			Node *node = expression->accept_r(this);
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

	Node *visit(ContinueStatement *s) {
		return s;
	}

	Node *visit(DoWhileStatement *s) {
		Node *condition = s->condition->accept_r(this);
		Node *statement = s->statement->accept_r(this);
		if (condition != s->condition || statement != s->statement) {
			return new DoWhileStatement(dynamic_cast<Expression*>(condition), consumeStatement(statement));
		}
		return s;
	}

	Node *visit(ForStatement *s) {
		Node *initialization = s->initialization->accept_r(this);
		Node *termination = s->termination->accept_r(this);
		Node *increment = s->increment->accept_r(this);
		Node *statement = s->statement->accept_r(this);
		if (initialization != s->initialization || termination != s->termination
			|| increment != s->increment || statement != s->statement) {
			return new ForStatement(
				consumeStatement(initialization),
				dynamic_cast<Expression*>(termination), consumeStatement(increment), consumeStatement(statement)
			);
		}
		return s;
	}

	Node *visit(ForeachStatement *s) {
		Node *container = s->container->accept_r(this);
		Node *body = s->body->accept_r(this);
		if (container != s->container || body != s->body) {
			return new ForeachStatement(s->key, s->val, dynamic_cast<Expression*>(container), consumeStatement(body));
		}
		return s;
	}

	Node *visit(FunctionDefineStatement *s){
		Arguments newArgs = Arguments();
		bool changed = visit_t(s->args, newArgs);

		Node *body = s->body->accept_r(this);
		if (changed || body != s->body) {
			return new FunctionDefineStatement(s->name, newArgs, consumeStatement(body), s->is_constexpr);
		}
		return s;
	}

	Node *visit(ExprStatement *s) {
		Node *expr = s->expr->accept_r(this);
		if (expr != s->expr) {
			return new ExprStatement(dynamic_cast<Expression*>(expr));
		}
		return s;
	}

	Node *visit(FunctionalExpression *s) {
		
		Node *function_expr = s->function_expr->accept_r(this);
		FunctionalExpression *result = new FunctionalExpression(dynamic_cast<Expression*>(function_expr));
		bool changed = function_expr != s->function_expr;

		for (Expression *argument : s->arguments) {
			Node *expr = argument->accept_r(this);
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

	Node *visit(IfStatement *s) {
		Node *expression = s->expression->accept_r(this);
		Node *if_statement = s->if_statement->accept_r(this);
		Node *else_statement;
		if (s->else_statement != NULL) {
			else_statement = s->else_statement->accept_r(this);
		} else {
			else_statement = NULL;
		}
		if (expression != s->expression || if_statement != s->if_statement || else_statement != s->else_statement) {
			return new IfStatement(dynamic_cast<Expression*>(expression), consumeStatement(if_statement),
				(else_statement == NULL ? NULL : consumeStatement(else_statement)) );
		}
		return s;
	}

	Node *visit(MapExpression *s) {
		std::map<Expression*, Expression*> elements;

		bool changed = false;
		for (auto& entry : s->elements) {
			Node *key = entry.first->accept_r(this);
			Node *value = entry.second->accept_r(this);
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

	Node *visit(PrintStatement *s) {
		Node *expression = s->expression->accept_r(this);
		if (expression != s->expression) {
			return new PrintStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(PutStatement *s) {
		Node *expression = s->expression->accept_r(this);
		if (expression != s->expression) {
			return new PutStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(ReturnStatement *s) {
		Node *expression = s->expression->accept_r(this);
		if (expression != s->expression) {
			return new ReturnStatement(dynamic_cast<Expression*>(expression));
		}
		return s;
	}

	Node *visit(TernaryExpression *s) {
		Node *condition = s->condition->accept_r(this);
		Node *trueExpr = s->trueExpr->accept_r(this);
		Node *falseExpr = s->falseExpr->accept_r(this);
		if (condition != s->condition || trueExpr != s->trueExpr || falseExpr != s->falseExpr) {
			return new TernaryExpression(dynamic_cast<Expression*>(condition), dynamic_cast<Expression*>(trueExpr), dynamic_cast<Expression*>(falseExpr));
		}
		return s;
	}

	Node *visit(UnaryExpression *s) {
		Node *expr = s->expr->accept_r(this);
		if (expr != s->expr) {
			return new UnaryExpression(s->operation, dynamic_cast<Expression*>(expr));
		}
		return s;
	}

	Node *visit(ValueExpression *s) {
		if ( (s->value->type() == Types::T_FUNCTION) && dynamic_cast<UserDefineFunction*>(s->value) ) {
			UserDefineFunction *function = dynamic_cast<UserDefineFunction*>(s->value);
			UserDefineFunction *accept_red = visit(function);
			if (accept_red != function) {
				return new ValueExpression(accept_red);
			}
		}
		return s;
	}

	Node *visit(VariableExpression *s) {
		return s;
	}

	Node *visit(WhileStatement *s) {
		Node *condition = s->condition->accept_r(this);
		Node *statement = s->statement->accept_r(this);
		if (condition != s->condition || statement != s->statement) {
			return new WhileStatement(dynamic_cast<Expression*>(condition), consumeStatement(statement));
		}
		return s;
	}

	Node *visit(UseStatement *s) {
		return s;
	}

	UserDefineFunction *visit(UserDefineFunction *s){
		
		Arguments newArgs = Arguments();
		bool changed = visit_t(s->args, newArgs);
		Node *body = s->body->accept_r(this);

		if (changed || body != s->body) {
			return new UserDefineFunction(newArgs, consumeStatement(body));
		}
		return s;
	}
private:
	bool visit_t(Arguments in, Arguments out){
		bool changed = false;
		for (int i = 0; i < in.get_size(); ++i) {
			Argument argument = in.get(i);
			Expression *valueExpr = argument.get_value_expr();
			if (valueExpr == NULL) {
				out.add_required(argument.get_name());
			} else {
				Node *expr = valueExpr->accept_r(this);
				if (expr != valueExpr) {
					changed = true;
				}
				out.add_optional(argument.get_name(), dynamic_cast<Expression*>(expr));
			}

		}
		return changed;
	}

	Statement* consumeStatement(Node *node) {
		if (dynamic_cast<Statement*>(node)) {
			return dynamic_cast<Statement*>(node);
		}
		return new ExprStatement(dynamic_cast<Expression*>(node));
	}

};

#endif