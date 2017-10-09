#ifndef LL_UTIL_CONSTANT_FOLDING_CPP
#define LL_UTIL_CONSTANT_FOLDING_CPP

#include "../optimizable.h"
#include "../../visitors/visitor_utils.cpp"
#include "../optimization_visitor.cpp"

namespace NS_ConstantFolding{
	static std::vector<std::string> OPERATORS = VisitorUtils::operators();
}

class ConstantFolding : public OptimizationVisitor, public Optimizable {
// class ConstantFolding : public OptimizationVisitor {
private:
	int binary_expression_folding_count;
	int conditional_expression_folding_count;
	int unary_expression_folding_count;
	std::vector<std::string> overloaded_operators;
public:

	ConstantFolding() {}

	Statement *optimize(Statement *statement) {
		// statement->accept_r(this);
		return NULL;
	}

	int optimizations_count() {
		return binary_expression_folding_count
		+ conditional_expression_folding_count
		+ unary_expression_folding_count;
	}

	std::string summary_info() {
		if (optimizations_count() == 0) return "";

		std::string sb;

		if (binary_expression_folding_count > 0) {
			sb += "\nBinaryExpression foldings: ";
			sb.push_back(binary_expression_folding_count);
		}
		if (conditional_expression_folding_count > 0) {
			sb += "\nConditionalExpression foldings: ";
			sb.push_back(conditional_expression_folding_count);
		}
		if (unary_expression_folding_count > 0) {
			sb += "\nUnaryExpression foldings: ";
			sb.push_back(unary_expression_folding_count);
		}

		return sb;
	}

	Node *visit(BinaryExpression *s) {
		if (overloaded_operators_contains(NS_Binary::OperatorString[s->operation])) {
			return ResultVisitor::visit(s);
		}
		if ( dynamic_cast<ValueExpression*>(s->expr1) && dynamic_cast<ValueExpression*>(s->expr2) ) {
			binary_expression_folding_count++;
			try {
				return new ValueExpression(s->eval());
			} catch (OperationIsNotSupportedException& op) {
				binary_expression_folding_count--;
			}
		}
		return ResultVisitor::visit(s);
	}

	Node *visit(ConditionalExpression *s) {
		if (overloaded_operators_contains(NS_Conditional::OperatorString[s->operation])) {
			return ResultVisitor::visit(s);
		}
		if ( dynamic_cast<ValueExpression*>(s->expr1) && dynamic_cast<ValueExpression*>(s->expr2) ) {
			conditional_expression_folding_count++;
			try {
				return new ValueExpression(s->eval());
			} catch (OperationIsNotSupportedException& op) {
				conditional_expression_folding_count--;
			}
		}
		return ResultVisitor::visit(s);
	}

	Node *visit(UnaryExpression* s) {
		if (overloaded_operators_contains(NS_Unary::OperatorString[s->operation])) {
			return ResultVisitor::visit(s);
		}
		if (dynamic_cast<ValueExpression*>(s->expr)) {
			unary_expression_folding_count++;
			try {
				return new ValueExpression(s->eval());
			} catch (OperationIsNotSupportedException& op) {
				unary_expression_folding_count--;
			}
		}
		return ResultVisitor::visit(s);
	}

	Node *visit(FunctionDefineStatement *s) {
		if (operators_contains(s->name)) {
			overloaded_operators.push_back(s->name);
		}
		return ResultVisitor::visit(s);
	}
private:
	bool operators_contains(std::string val) {
		return find(NS_ConstantFolding::OPERATORS.begin(), NS_ConstantFolding::OPERATORS.end(), val) != NS_ConstantFolding::OPERATORS.end();
	}
	bool overloaded_operators_contains(std::string val) {
		return find(overloaded_operators.begin(), overloaded_operators.end(), val) != overloaded_operators.end();
	}
};

#endif