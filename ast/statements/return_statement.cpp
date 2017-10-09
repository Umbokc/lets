#ifndef LL_RETURN_STATEMENT_CPP
#define LL_RETURN_STATEMENT_CPP
#include <string>

class ReturnStatement : public Statement{
public:
	Value *result;
	Expression *expression;

	ReturnStatement(Expression *expression){
		this->expression = expression;
	}

	Value *get_result(){
		return result;
	}

	void execute(){
		result = expression->eval();
		throw this;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return "return";
	}

	~ReturnStatement(){
		// delete[] result;
		// delete[] expression;
	}

};

#endif
