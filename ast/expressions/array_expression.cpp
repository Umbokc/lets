#ifndef ARRAY_EXPRESSION_H
#define ARRAY_EXPRESSION_H

#include <vector>
#include <string>

class ArrayExpression : public Expression{
public:
	std::vector<Expression *> elements;

	ArrayExpression(std::vector<Expression *> elements)
											:elements(std::move(elements)){}

	Value *eval(){
		// ArrayValue *array = new ArrayValue(elements);

		int size = elements.size();
		ArrayValue *array = new ArrayValue(size);

		for (int i = 0; i < size; i++) {
			array->set(i, elements[i]->eval());
		}

		return array;
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

	~ArrayExpression(){}
};

#endif