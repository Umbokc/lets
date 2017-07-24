#ifndef UNARY_EXPRESSION_H
#define UNARY_EXPRESSION_H

#include <string>

namespace UnaryOperator{

	static enum Operator{
    INCREMENT_PREFIX, // ++
    DECREMENT_PREFIX, // --
    INCREMENT_POSTFIX, // ++
    DECREMENT_POSTFIX, // --
    NEGATE, // -
    // Boolean
    NOT, // !
    // Bitwise
    COMPLEMENT, // ~
	} x;

	const static std::string OperatorString[] {
    "++",
    "--",
    "++",
    "--",
    "-",
    // Boolean
    "!",
    // Bitwise
    "~",
	};
	
}

class UnaryExpression : public Expression{
public:

	UnaryOperator::Operator operation;
	Expression *expr;

	UnaryExpression(UnaryOperator::Operator operation,
		Expression* expr): 
		operation(std::move(operation)), expr(std::move(expr)){}

	Value *eval() {
		Value *value = expr->eval();
		switch (operation) {
			case UnaryOperator::Operator::INCREMENT_PREFIX:
				return UO_increment(value);
			case UnaryOperator::Operator::INCREMENT_POSTFIX:
				// if(auto v1 = dynamic_cast<VariableExpression>(value)){
					// VariableExpression::set(UO_increment(value));
					// return value;
				// }
				return UO_increment(value);
			case UnaryOperator::Operator::DECREMENT_PREFIX:
				return UO_decrement(value);
			case UnaryOperator::Operator::DECREMENT_POSTFIX:
				// if(value instanceof VariableExpression){
					// VariableExpression::set(UO_decrement(value));
					// return value;
				// }
				return UO_decrement(value);
			case UnaryOperator::Operator::COMPLEMENT:
				return UO_complement(value);
			case UnaryOperator::Operator::NEGATE:
				return UO_negate(value);
			case UnaryOperator::Operator::NOT:
				return UO_not(value);
			default:
				throw ParseException("Operation Is Not Supported");
		}
	}
	
	Value *UO_increment(Value *value){
		if(value->type() == Types::T_STRING) {
			std::string newval = value->as_string();
			if(newval == "") return ONE;
			newval.back() = ++newval.back();
			return new StringValue(newval);
		}

		return new NumberValue(value->as_number() + 1);
	}
	
	Value *UO_decrement(Value *value){
		if(value->type() == Types::T_STRING) {
			std::string newval = value->as_string();
			if(newval == "") return NEGATE_ONE;
			newval.back() = --newval.back();
			return new StringValue(newval);
		} 
		return new NumberValue(value->as_number() - 1);
	}
	
	Value *UO_complement(Value *value){
		return new NumberValue(~(int)value->as_number());
	}

	Value *UO_negate(Value *value){
		if(value->type() == Types::T_NUMBER){
		
			return new NumberValue(-value->as_number());
		
		} else if(value->type() == Types::T_STRING){
			
			return new StringValue(func::reverse_s(value->as_string()));

		} else if(value->type() == Types::T_ARRAY){
			
			auto new_arr = dynamic_cast<ArrayValue*>(value)->get_all();
			func::reverse(std::begin(new_arr), std::end(new_arr));
			return new ArrayValue(new_arr);
		
		}

		return ZERO;
	}
	
	Value *UO_not(Value *value){
		if(value->type() == Types::T_NUMBER){
			return new NumberValue(value->as_number() == 0);
		} else if(value->type() == Types::T_STRING){
			return new NumberValue(value->as_string() == "");
		}
		return ZERO;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return func::string_format(
			"[%s %s]",  
			UnaryOperator::OperatorString[operation].c_str(),
			expr->to_s().c_str()
		);
	}

	~UnaryExpression(){
		// delete[] expr;
	}
};
#endif
