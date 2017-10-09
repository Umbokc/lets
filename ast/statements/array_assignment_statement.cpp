#ifndef ARRAY_ASSIGNMENT_STATEMENT_CPP
#define ARRAY_ASSIGNMENT_STATEMENT_CPP

#include <string>

class ArrayAssignmentStatement : public Statement{
public:
	Expression *expression;
	ArrayAccessExpression *array;

	ArrayAssignmentStatement(ArrayAccessExpression *array, Expression *expression){
		this->array = array;
		this->expression = expression;
	}

	void execute(){
		array->get_array()->set(array->last_index(),expression->eval());
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return array->to_s() + " = " + expression->to_s();
	}

	~ArrayAssignmentStatement(){
		// delete[] expression;
		// delete[] array;
	}

};

#endif
