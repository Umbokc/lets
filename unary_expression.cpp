#ifndef UNARY_EXPRESSION_H
#define UNARY_EXPRESSION_H

#include <string>

namespace NS_Unary{

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
    "++(prefix)",
    "--(prefix)",
    "(postfix)++",
    "(postfix)--",
    "-",
    // Boolean
    "!",
    // Bitwise
    "~",
	};
	
}

class UnaryExpression : public Expression, public Statement{
public:

	NS_Unary::Operator operation;
	Expression *expr;

	UnaryExpression(NS_Unary::Operator operation,
		Expression* expr): 
		operation(std::move(operation)), expr(std::move(expr)){}

	void execute(){
		eval();
	}

	Value *eval() {
		Value *value = expr->eval();
		switch (operation) {
			case NS_Unary::Operator::INCREMENT_PREFIX:
				if(dynamic_cast<Accessible*>(expr)){
					return dynamic_cast<Accessible*>(expr)->set(UE_increment(value));
				}
				return UE_increment(value);
			case NS_Unary::Operator::INCREMENT_POSTFIX:
				if(dynamic_cast<Accessible*>(expr)){
					dynamic_cast<Accessible*>(expr)->set(UE_increment(value));
					return value;
				}
				return UE_increment(value);
			case NS_Unary::Operator::DECREMENT_PREFIX:
				if(dynamic_cast<Accessible*>(expr)){
					return dynamic_cast<Accessible*>(expr)->set(UE_decrement(value));
				}
				return UE_decrement(value);
			case NS_Unary::Operator::DECREMENT_POSTFIX:
				if(dynamic_cast<Accessible*>(expr)){
					dynamic_cast<Accessible*>(expr)->set(UE_decrement(value));
					return value;
				}
				return UE_decrement(value);
			case NS_Unary::Operator::NEGATE:
				return UE_negate(value);
			case NS_Unary::Operator::NOT:
				return UE_not(value);
			case NS_Unary::Operator::COMPLEMENT:
				return UE_complement(value);
			default:
				throw ParseException("Operation Is Not Supported");
		}
	}
	
	Value *UE_increment(Value *value){
		if(value->type() == Types::T_STRING) {
			std::string newval = value->as_string();
			if(newval == "") return ONE;
			newval.back() = ++newval.back();
			return new StringValue(newval);
		}

		return new NumberValue(value->as_number() + 1);
	}
	
	Value *UE_decrement(Value *value){
		if(value->type() == Types::T_STRING) {
			std::string newval = value->as_string();
			if(newval == "") return NEGATE_ONE;
			newval.back() = --newval.back();
			return new StringValue(newval);
		} 
		return new NumberValue(value->as_number() - 1);
	}
	
	Value *UE_complement(Value *value){
		return new NumberValue(~(int)value->as_number());
	}

	Value *UE_negate(Value *value){
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
	
	Value *UE_not(Value *value){
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
			NS_Unary::OperatorString[operation].c_str(),
			expr->to_s().c_str()
		);
	}

	~UnaryExpression(){
		// delete[] expr;
	}
};
#endif
