//
//  e_binary_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__expr__binary_hpp
#define ast__expr__binary_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "l_number_value.hpp"

namespace NS_Binary{
	typedef enum{
		//	+			-					*				/					%
		ADD, SUBTRACT, MULTIPLY, DIVIDE, REMAINDER,
		// &		|		^			<<		  >>
		AND, OR, XOR, LSHIFT, RSHIFT, THE_NULL
	} Operator;

	const static lets_str_t OperatorString[] = {
		"+", "-", "*", "/", "%",
		// Bitwise
		"&", "|", "^", "<<", ">>", "="
	};
}

class BinaryExpression : virtual public Expression{
public:

	NS_Binary::Operator operation;
	Expression* expr1;
	Expression* expr2;

	BinaryExpression();
	BinaryExpression(NS_Binary::Operator operation, Expression* expr1, Expression* expr2);

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	Value * eval();

	lets_str_t to_s();

	~BinaryExpression();
private:

	Value *eval(Value*, Value*);

	Value *BO_add(Value*, Value*);
	Value *BO_add(NumberValue*, Value*);
	Value *BO_subtract(Value*, Value*);
	Value *BO_multiply(Value*, Value*);
	Value *BO_divide(Value*, Value*);
	Value *BO_remainder(Value*, Value*);
	Value *BO_and(Value*, Value*);
	Value *BO_or(Value*, Value*);
	Value *BO_xor(Value*, Value*);
	Value *BO_lshift(Value*, Value*);

	Value *BO_rshift(Value*, Value*);
	void operation_is_not_supported();
};

#endif /* ast__expr__binary_hpp */
