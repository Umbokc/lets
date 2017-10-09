#ifndef MATCH_EXPRESSION_H
#define MATCH_EXPRESSION_H

#include <vector>
#include <string>

class MatchExpression : public Expression, public Statement{
public:
	std::vector<Expression *> elements;
	// std::vector<Expression *> elements;

	MatchExpression(std::vector<Expression *> elements)
											:elements(std::move(elements)){}

	Value *eval(){
		return NULL;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return "[ " + func::vector_to_s<Expression *>(elements) + " ]";
	}

	~MatchExpression();
};

#endif