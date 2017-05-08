#ifndef TERNARYEXPRESSION_H
#define TERNARYEXPRESSION_H

TernaryExpression::TernaryExpression(Expression *condition, Expression *trueExpr, Expression *falseExpr){
	this->condition = condition;
	this->trueExpr = trueExpr;
	this->falseExpr = falseExpr;
}

Value* TernaryExpression::eval(){
	if (condition->eval()->asNumber() != 0) {
		return trueExpr->eval();
	} else {
		return falseExpr->eval();
	}
}

void TernaryExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string TernaryExpression::to_s(){
	return condition->to_s() + " ? " + trueExpr->to_s() + " : " + falseExpr->to_s();
}

#endif
