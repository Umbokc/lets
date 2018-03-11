//
//  include/keyword.hpp
//  lets
//
//  Created by Dragan Stepan on 11.03.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__keyword_hpp
#define include__keyword_hpp

#include <string>
#include "main.h"
#include "../lib/array.h"

#define GET_KW(KW) Keywords::KW
#define GET_KW_BY(TXT) Keywords::get_kw(TXT)
#define GET_KW_TEXT(KW) Keywords::get_text(Keywords::KW)
#define GET_KW_TO_S(KW) Keywords::get_text(KW)

namespace Keywords {

	extern lets_array_t<lets_str_t> keywords_text;

	#define DECLARE_KEYWORD(NUM, NAME) \
		const u_tt_t NAME = NUM;

		DECLARE_KEYWORD(0, NIL)
		DECLARE_KEYWORD(1, PRINT)
		DECLARE_KEYWORD(2, PUT)
		DECLARE_KEYWORD(3, IF)
		DECLARE_KEYWORD(4, ELSE)
		DECLARE_KEYWORD(5, ELIF)
		DECLARE_KEYWORD(6, WHILE)
		DECLARE_KEYWORD(7, FOR)
		DECLARE_KEYWORD(8, DO)
		DECLARE_KEYWORD(9, BREAK)
		DECLARE_KEYWORD(10, CONTINUE)
		DECLARE_KEYWORD(11, DEF)
		DECLARE_KEYWORD(12, RETURN)
		DECLARE_KEYWORD(13, USE)
		DECLARE_KEYWORD(14, END)
		DECLARE_KEYWORD(15, IN)
		DECLARE_KEYWORD(16, MODE)
		DECLARE_KEYWORD(17, MATCH)
		DECLARE_KEYWORD(18, CASE)
		DECLARE_KEYWORD(19, DEFAULT)
		DECLARE_KEYWORD(20, AND)
		DECLARE_KEYWORD(21, OR)
		DECLARE_KEYWORD(22, NOT)
		DECLARE_KEYWORD(23, INCLUDE)
		DECLARE_KEYWORD(24, NEW)
		DECLARE_KEYWORD(25, CLASS)

	const lets_str_t get_text(const u_tt_t&);
	const u_tt_t get_kw(const lets_str_t&);

};

#endif /* include__keyword_hpp */

