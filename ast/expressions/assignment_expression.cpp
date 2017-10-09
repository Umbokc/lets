#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include <string>

class AssignmentExpression : public Expression, public Statement{
public:

	NS_Binary::Operator operation;
	Accessible *target;
	Expression *expression;


	AssignmentExpression(
		NS_Binary::Operator operation,
		Accessible *target,
		Expression *expression)
		:
		operation(operation),
		target(std::move(target)),
		expression(std::move(expression)){}

	void execute(){
		eval();
	}

	Value* eval(){

		if(operation == NS_Binary::Operator::THE_NULL){
			return target->set(expression->eval());
		}

		Expression *expr1 = new ValueExpression(target->get());
		Expression *expr2 = new ValueExpression(expression->eval());
		Expression *res_expr = new BinaryExpression(operation, expr1, expr2);

		Value *result = target->set(res_expr->eval());

		return result;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return func::string_format(
			"[%s %s %s]",  
			target->to_s().c_str(),
			NS_Binary::OperatorString[operation].c_str(),
			expression->to_s().c_str()
		);
	}
	~AssignmentExpression(){
		// delete[] target;
		// delete[] falseExpr;
	}
};

#endif
