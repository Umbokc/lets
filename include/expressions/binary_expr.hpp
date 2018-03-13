//
//  include/expressions/binary_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_binary_hpp
#define include__e_binary_hpp

#include <string>
#include "../main.h"
#include "../expression.h"
#include "../lib/number_value.hpp"

namespace NS_Binary{
	typedef enum{
	// +      -         *        /        %
		ADD, SUBTRACT, MULTIPLY, DIVIDE, REMAINDER,
	// &   |    ^     <<      >>     **
		AND, OR, XOR, LSHIFT, RSHIFT, POWER, THE_NULL
	} Operator;

	const static lets_str_t OperatorString[] = {
		"+", "-", "*", "/", "%",
		// Bitwise
		"&", "|", "^", "<<", ">>", "**", ""
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

	Value *bin_op_add(Value*, Value*);
	Value *bin_op_add(NumberValue*, Value*);
	Value *bin_op_subtract(Value*, Value*);
	Value *bin_op_multiply(Value*, Value*);
	Value *bin_op_divide(Value*, Value*);
	Value *bin_op_remainder(Value*, Value*);
	Value *bin_op_and(Value*, Value*);
	Value *bin_op_or(Value*, Value*);
	Value *bin_op_xor(Value*, Value*);
	Value *bin_op_lshift(Value*, Value*);
	Value *bin_op_rshift(Value*, Value*);
	Value *bin_op_power(Value*, Value*);

	int power(int, int);
	void operation_is_not_supported();
};

#endif /* include__e_binary_hpp */
