//
//  include/operator.h
//  lets
//
//  Created by Dragan Stepan on 10.03.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__operator_h
#define include__operator_h

#include <string>
#include "main.h"
#include "../lib/array.h"

#define GET_OP(OP) Operators::OP
#define GET_OP_BY(TXT) Operators::get_op(TXT)
#define GET_OP_TEXT(OP) Operators::get_text(Operators::OP)
#define GET_OP_TO_S(OP) Operators::get_text(OP)

namespace Operators {

	extern lets_array_t<lets_str_t> operators_text;

	#define DECLARE_OPERATOR(NUM, NAME) \
		const u_tt_t NAME = NUM;

		DECLARE_OPERATOR(0, NIL)

		DECLARE_OPERATOR(1, PLUS)
		DECLARE_OPERATOR(2, MINUS)
		DECLARE_OPERATOR(3, STAR)
		DECLARE_OPERATOR(4, SLASH)

		DECLARE_OPERATOR(5, BACKSLASH)
		DECLARE_OPERATOR(6, PERCENT)
		DECLARE_OPERATOR(7, EQ)

		DECLARE_OPERATOR(8, EQEQ)
		DECLARE_OPERATOR(9, EXCL)
		DECLARE_OPERATOR(10, EXCLEQ)
		DECLARE_OPERATOR(11, LTEQ)
		DECLARE_OPERATOR(12, LT)
		DECLARE_OPERATOR(13, GT)
		DECLARE_OPERATOR(14, GTEQ)

		DECLARE_OPERATOR(15, PLUSEQ)
		DECLARE_OPERATOR(16, MINUSEQ)
		DECLARE_OPERATOR(17, STAREQ)
		DECLARE_OPERATOR(18, SLASHEQ)
		DECLARE_OPERATOR(19, PERCENTEQ)
		DECLARE_OPERATOR(20, AMPEQ)
		DECLARE_OPERATOR(21, CARETEQ)
		DECLARE_OPERATOR(22, BAREQ)

		DECLARE_OPERATOR(23, PLUSPLUS)
		DECLARE_OPERATOR(24, MINUSMINUS)

		DECLARE_OPERATOR(25, LTLT)
		DECLARE_OPERATOR(26, GTGT)
		DECLARE_OPERATOR(27, DOTDOT)
		DECLARE_OPERATOR(28, STARSTAR)
		DECLARE_OPERATOR(29, TILDE)
		DECLARE_OPERATOR(30, CARET)
		DECLARE_OPERATOR(31, BAR)
		DECLARE_OPERATOR(32, BARBAR)
		DECLARE_OPERATOR(33, AMP)
		DECLARE_OPERATOR(34, AMPAMP)
		DECLARE_OPERATOR(35, QUESTION)
		DECLARE_OPERATOR(36, COLON)
		DECLARE_OPERATOR(37, COLONCOLON)

		DECLARE_OPERATOR(38, LPAREN)
		DECLARE_OPERATOR(39, RPAREN)
		DECLARE_OPERATOR(40, LBRACKET)
		DECLARE_OPERATOR(41, RBRACKET)
		DECLARE_OPERATOR(42, LBRACE)
		DECLARE_OPERATOR(43, RBRACE)

		DECLARE_OPERATOR(44, COMMA)
		DECLARE_OPERATOR(45, DOT)
		DECLARE_OPERATOR(46, LTMINUS)
		DECLARE_OPERATOR(47, EQGT)

		DECLARE_OPERATOR(48, EQEQEQ)
		DECLARE_OPERATOR(49, EXCLEQEQ)

	const lets_str_t get_text(const u_tt_t&);
	const u_tt_t get_op(const lets_str_t&);

};

#endif /* include__operator_h */

