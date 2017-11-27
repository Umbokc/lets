//
//  e_unary_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef e_unary_expr_hpp
#define e_unary_expr_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class UnaryExpression : public Expression, public Statement{
public:

	typedef enum{
		INCREMENT_PREFIX, // ++
		DECREMENT_PREFIX, // --
		INCREMENT_POSTFIX, // ++
		DECREMENT_POSTFIX, // --
		NEGATE, // -
		// Boolean
		NOT, // !
		// Bitwise
		COMPLEMENT, // ~
	} Operator;

	const static lets_str_t OperatorString[7];

	Operator operation;
	Expression *expr;
	
	UnaryExpression(Operator,Expression*);
	
	void execute();
	
	Value *eval();
	
	Value *UE_increment(Value*);
	Value *UE_decrement(Value*);
	Value *UE_complement(Value*);
	Value *UE_negate(Value*);
	Value *UE_not(Value*);
	
	lets_str_t to_s();
	
	~UnaryExpression();
private:
	lets_str_t reverse(const lets_str_t& the);
	
	template<class BidirIt>
	void reverse(BidirIt first, BidirIt last){
		while ((first != last) && (first != --last)) {
			std::swap(*first++, *last);
		}
	}
};

#endif /* e_unary_expr_hpp */
