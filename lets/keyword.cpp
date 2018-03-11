//
//  lets/keyword.cpp
//  lets
//
//  Created by Dragan Stepan on 11.03.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include "../include/keyword.hpp"

namespace Keywords{

	#define DEFINE_KEYWORD(NAME, TEXT) \
		TEXT,

	#define DEFINE_KEYWORDS() \
		lets_array_t<lets_str_t> keywords_text{ \
			DEFINE_KEYWORD(NIL, "") \
			DEFINE_KEYWORD(PRINT, "print") \
			DEFINE_KEYWORD(PUT, "put") \
			DEFINE_KEYWORD(IF, "if") \
			DEFINE_KEYWORD(ELSE, "else") \
			DEFINE_KEYWORD(ELIF, "elif") \
			DEFINE_KEYWORD(WHILE, "while") \
			DEFINE_KEYWORD(FOR, "for") \
			DEFINE_KEYWORD(DO, "do") \
			DEFINE_KEYWORD(BREAK, "break") \
			DEFINE_KEYWORD(CONTINUE, "continue") \
			DEFINE_KEYWORD(DEF, "def") \
			DEFINE_KEYWORD(RETURN, "return") \
			DEFINE_KEYWORD(USE, "use") \
			DEFINE_KEYWORD(END, "end") \
			DEFINE_KEYWORD(IN, "in") \
			DEFINE_KEYWORD(MODE, "mode") \
			DEFINE_KEYWORD(MATCH, "match") \
			DEFINE_KEYWORD(CASE, "case") \
			DEFINE_KEYWORD(DEFAULT, "default") \
			DEFINE_KEYWORD(AND, "and") \
			DEFINE_KEYWORD(OR, "or") \
			DEFINE_KEYWORD(NOT, "not") \
			DEFINE_KEYWORD(INCLUDE, "include") \
			DEFINE_KEYWORD(NEW, "new") \
			DEFINE_KEYWORD(CLASS, "class") \
		};

	DEFINE_KEYWORDS()


	const lets_str_t get_text(const u_tt_t &t) {
		return keywords_text[t];
	}

	const u_tt_t get_kw(const lets_str_t &s) {
		if(keywords_text.has(s))
			return (u_tt_t) keywords_text.find(s);
		else
			return NIL;
	}

}
