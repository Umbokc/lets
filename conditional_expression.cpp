#ifndef CONDITIONAL_EXPRESSION_H
#define CONDITIONAL_EXPRESSION_H

#include <string>

namespace ConditionalOperator{
	static enum Operator {EQUALS, NOT_EQUALS, LT, LTEQ, GT, GTEQ, AND, OR } x;
	static const std::string OperatorString[] =  { "==", "!=", "<", "<=", ">", ">=", "&&", "||" };
}

class ConditionalExpression : public Expression{
public:

	ConditionalOperator::Operator operation;
	Expression *expr1;
	Expression *expr2;


	ConditionalExpression(ConditionalOperator::Operator operation,
		Expression* expr1, Expression* expr2): 
		operation(std::move(operation)), 
		expr1(std::move(expr1)), expr2(std::move(expr2)){}

	Value* eval(){
		Value* value1 = expr1->eval();
		Value* value2 = expr2->eval();

		double number1, number2;

		// if(Value* v1 = dynamic_cast<StringValue*>(value1)){
		if(value1->type() == Types::T_STRING){
			number1 = compareTo(value1->as_string(), value2->as_string());
			number2 = 0;
		} else {
			number1 = value1->as_number();
			number2 = value2->as_number();
		}

		bool result;

		switch(operation){
			case ConditionalOperator::LT : result = (number1 < number2); break;
			case ConditionalOperator::LTEQ : result = (number1 <= number2); break;
			case ConditionalOperator::GT : result = (number1 > number2); break;
			case ConditionalOperator::GTEQ : result = (number1 >= number2); break;
			case ConditionalOperator::NOT_EQUALS : result = (number1 != number2); break;	
			case ConditionalOperator::EQUALS : result = (number1 == number2); break;	

			case ConditionalOperator::AND: result = (number1 != 0 && number2 != 0); break;	
			case ConditionalOperator::OR : result = (number1 != 0 || number2 != 0); break;	

			default: 
				throw ParseException("Operation is not supported");
		}

		return new NumberValue(result);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){ 
		return func::string_format(
			"[%s %s %s]",  
			expr1->to_s().c_str(),
			ConditionalOperator::OperatorString[operation].c_str(),
			expr2->to_s().c_str()
		);
	}

	int compareTo(std::string const & s1, std::string const & s2) {
		return (s1 > s2) ? 1 : (s1 < s2) ? -1 : 0;
	}

	~ConditionalExpression(){
		// delete[] expr1;
		// delete[] expr2;
	}
};

#endif