#ifndef TERNARY_EXPRESSION_H
#define TERNARY_EXPRESSION_H

#include <string>

class TernaryExpression : public Expression{
public:
	Expression *condition;
	Expression *trueExpr, *falseExpr;


	TernaryExpression(
		Expression *condition,
		Expression *trueExpr,
		Expression *falseExpr)
		:
		condition(std::move(condition)),
		trueExpr(std::move(trueExpr)),
		falseExpr(std::move(falseExpr)){}

	Value* eval(){
		if (condition->eval()->as_number() != 0) {
			return trueExpr->eval();
		} else {
			return falseExpr->eval();
		}
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return condition->to_s() + " ? " + trueExpr->to_s() + " : " + falseExpr->to_s();
	}
	
	~TernaryExpression(){
		// delete[] condition;
		// delete[] trueExpr;
		// delete[] falseExpr;
	}
};

#endif
