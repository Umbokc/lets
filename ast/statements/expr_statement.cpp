#ifndef EXPR_STATEMENT_H
#define EXPR_STATEMENT_H

class ExprStatement : public Expression, public Statement{
public:
	Expression *expr;

	ExprStatement(Expression *function):
		expr(std::move(function))
	{}

	void execute(){
		eval();
	}

	Value *eval(){
		return expr->eval();
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return expr->to_s();
	}

	~ExprStatement(){
		// delete[] expr;
	}
};

#endif
