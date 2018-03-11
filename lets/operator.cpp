//
//  lets/operator.cpp
//  lets
//
//  Created by Dragan Stepan on 10.03.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

// #include <iostream>
#include "../include/operator.hpp"

namespace Operators{
	// lets_array_t<lets_str_t> operators_text(48);

	#define DEFINE_OPERATOR(NAME, TEXT) \
		TEXT, \
		// operators_text.set(NAME, TEXT);

	#define DEFINE_OPERATORS() \
		lets_array_t<lets_str_t> operators_text{ \
			DEFINE_OPERATOR(NIL, "") \
			DEFINE_OPERATOR(PLUS, "+") \
			DEFINE_OPERATOR(MINUS, "-") \
			DEFINE_OPERATOR(STAR, "*") \
			DEFINE_OPERATOR(SLASH, "/") \
			DEFINE_OPERATOR(BACKSLASH, "\\") \
			DEFINE_OPERATOR(PERCENT, "%") \
			DEFINE_OPERATOR(EQ, "=") \
			DEFINE_OPERATOR(EQEQ, "==") \
			DEFINE_OPERATOR(EXCL, "!") \
			DEFINE_OPERATOR(EXCLEQ, "!=") \
			DEFINE_OPERATOR(LTEQ, "<=") \
			DEFINE_OPERATOR(LT, "<") \
			DEFINE_OPERATOR(GT, ">") \
			DEFINE_OPERATOR(GTEQ, ">=") \
			DEFINE_OPERATOR(PLUSEQ, "+=") \
			DEFINE_OPERATOR(MINUSEQ, "-=") \
			DEFINE_OPERATOR(STAREQ, "*=") \
			DEFINE_OPERATOR(SLASHEQ, "/=") \
			DEFINE_OPERATOR(PERCENTEQ, "%=") \
			DEFINE_OPERATOR(AMPEQ, "&=") \
			DEFINE_OPERATOR(CARETEQ, "^=") \
			DEFINE_OPERATOR(BAREQ, "|=") \
			DEFINE_OPERATOR(PLUSPLUS, "++") \
			DEFINE_OPERATOR(MINUSMINUS, "--") \
			DEFINE_OPERATOR(LTLT, "<<") \
			DEFINE_OPERATOR(GTGT, ">>") \
			DEFINE_OPERATOR(DOTDOT, "..") \
			DEFINE_OPERATOR(STARSTAR, "**") \
			DEFINE_OPERATOR(TILDE, "~") \
			DEFINE_OPERATOR(CARET, "^") \
			DEFINE_OPERATOR(BAR, "|") \
			DEFINE_OPERATOR(BARBAR, "||") \
			DEFINE_OPERATOR(AMP, "&") \
			DEFINE_OPERATOR(AMPAMP, "&&") \
			DEFINE_OPERATOR(QUESTION, "?") \
			DEFINE_OPERATOR(COLON, ":") \
			DEFINE_OPERATOR(COLONCOLON, "::") \
			DEFINE_OPERATOR(LPAREN, "(") \
			DEFINE_OPERATOR(RPAREN, ")") \
			DEFINE_OPERATOR(LBRACKET, "[") \
			DEFINE_OPERATOR(RBRACKET, "]") \
			DEFINE_OPERATOR(LBRACE, "{") \
			DEFINE_OPERATOR(RBRACE, "}") \
			DEFINE_OPERATOR(COMMA, ",") \
			DEFINE_OPERATOR(DOT, ".") \
			DEFINE_OPERATOR(LTMINUS, "<-") \
			DEFINE_OPERATOR(EQGT, "=>") \
			DEFINE_OPERATOR(EQEQEQ, "===") \
			DEFINE_OPERATOR(EXCLEQEQ, "!==") \
		};

	DEFINE_OPERATORS()


	const lets_str_t get_text(const u_tt_t &t) {
		return operators_text[t];
	}

	const u_tt_t get_op(const lets_str_t &s) {
		if(operators_text.has(s))
			return (u_tt_t) operators_text.find(s);
		else
			return NIL;
	}

}

