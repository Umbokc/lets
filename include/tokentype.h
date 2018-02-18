//
//  include/tokentype.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__tokentype_h
#define include__tokentype_h

#define TT_EOF 0
#define TT_EOF_TEXT "eof"


#define TT_NUMBER 1
#define TT_NUMBER_TEXT "number"

#define TT_HEX_NUMBER 2
#define TT_HEX_NUMBER_TEXT "hex_number"

#define TT_OCTAL_NUMBER 3
#define TT_OCTAL_NUMBER_TEXT "octal_number"

#define TT_BINARY_NUMBER 4
#define TT_BINARY_NUMBER_TEXT "binary_number"


#define TT_IDENTIFIER 5
#define TT_IDENTIFIER_TEXT "identifier"

#define TT_STRING 6
#define TT_STRING_TEXT "string"


#define TT_PLUS 7 // +
#define TT_PLUS_TEXT "+"
#define TT_PLUS_AS_STR "plus"

#define TT_MINUS 8 // -
#define TT_MINUS_TEXT "-"
#define TT_MINUS_AS_STR "minus"

#define TT_STAR 9 // *
#define TT_STAR_TEXT "*"
#define TT_STAR_AS_STR "star"

#define TT_SLASH 10 // /
#define TT_SLASH_TEXT "/"
#define TT_SLASH_AS_STR "slash"

#define TT_PERCENT 11 // %
#define TT_PERCENT_TEXT "%"
#define TT_PERCENT_AS_STR "percent"

#define TT_EQ 12 // =
#define TT_EQ_TEXT "="
#define TT_EQ_AS_STR "eq"

#define TT_EQEQ 13 // ==
#define TT_EQEQ_TEXT "=="
#define TT_EQEQ_AS_STR "eqeq"

#define TT_EXCL 14 // !
#define TT_EXCL_TEXT "!"
#define TT_EXCL_AS_STR "excl"

#define TT_EXCLEQ 15 // !=
#define TT_EXCLEQ_TEXT "!="
#define TT_EXCLEQ_AS_STR "excleq"

#define TT_LTEQ 16 // <=
#define TT_LTEQ_TEXT "<="
#define TT_LTEQ_AS_STR "lteq"

#define TT_LT 17 // <
#define TT_LT_TEXT "<"
#define TT_LT_AS_STR "lt"

#define TT_GT 18 // >
#define TT_GT_TEXT ">"
#define TT_GT_AS_STR "gt"

#define TT_GTEQ 19 // >=
#define TT_GTEQ_TEXT ">="
#define TT_GTEQ_AS_STR "gteq"

#define TT_PLUSEQ 20 // +=
#define TT_PLUSEQ_TEXT "+="
#define TT_PLUSEQ_AS_STR "pluseq"

#define TT_MINUSEQ 21 // -=
#define TT_MINUSEQ_TEXT "-="
#define TT_MINUSEQ_AS_STR "minuseq"

#define TT_STAREQ 22 // *=
#define TT_STAREQ_TEXT "*="
#define TT_STAREQ_AS_STR "stareq"

#define TT_SLASHEQ 23 // /=
#define TT_SLASHEQ_TEXT "/="
#define TT_SLASHEQ_AS_STR "slasheq"

#define TT_PERCENTEQ 24 // %=
#define TT_PERCENTEQ_TEXT "%="
#define TT_PERCENTEQ_AS_STR "percenteq"

#define TT_AMPEQ 25 // &=
#define TT_AMPEQ_TEXT "&="
#define TT_AMPEQ_AS_STR "ampeq"

#define TT_CARETEQ 26 // ^=
#define TT_CARETEQ_TEXT "^="
#define TT_CARETEQ_AS_STR "careteq"

#define TT_BAREQ 27 // |=
#define TT_BAREQ_TEXT "|="
#define TT_BAREQ_AS_STR "bareq"

#define TT_PLUSPLUS 28 // ++
#define TT_PLUSPLUS_TEXT "++"
#define TT_PLUSPLUS_AS_STR "plusplus"

#define TT_MINUSMINUS 29 // --
#define TT_MINUSMINUS_TEXT "--"
#define TT_MINUSMINUS_AS_STR "minusminus"

#define TT_LTLT 30 // <<
#define TT_LTLT_TEXT "<<"
#define TT_LTLT_AS_STR "ltlt"

#define TT_GTGT 31 // >>
#define TT_GTGT_TEXT ">>"
#define TT_GTGT_AS_STR "gtgt"

#define TT_DOTDOT 32 // ..
#define TT_DOTDOT_TEXT ".."
#define TT_DOTDOT_AS_STR "dotdot"

#define TT_STARSTAR 33 // **
#define TT_STARSTAR_TEXT "**"
#define TT_STARSTAR_AS_STR "starstar"

#define TT_TILDE 34 // ~
#define TT_TILDE_TEXT "~"
#define TT_TILDE_AS_STR "tilde"

#define TT_CARET 35 // ^
#define TT_CARET_TEXT "^"
#define TT_CARET_AS_STR "caret"

#define TT_BAR 36 // |
#define TT_BAR_TEXT "|"
#define TT_BAR_AS_STR "bar"

#define TT_BARBAR 37 // ||
#define TT_BARBAR_TEXT "||"
#define TT_BARBAR_AS_STR "barbar"

#define TT_AMP 38 // &
#define TT_AMP_TEXT "&"
#define TT_AMP_AS_STR "amp"

#define TT_AMPAMP 39 // &&
#define TT_AMPAMP_TEXT "&&"
#define TT_AMPAMP_AS_STR "ampamp"

#define TT_QUESTION 40 // ?
#define TT_QUESTION_TEXT "?"
#define TT_QUESTION_AS_STR "question"

#define TT_COLON 41 // :
#define TT_COLON_TEXT ":"
#define TT_COLON_AS_STR "colon"

#define TT_COLONCOLON 42 // ::
#define TT_COLONCOLON_TEXT "::"
#define TT_COLONCOLON_AS_STR "coloncolon"

#define TT_LPAREN 43  // (
#define TT_LPAREN_TEXT "("
#define TT_LPAREN_AS_STR "lparen"

#define TT_RPAREN 44 // )
#define TT_RPAREN_TEXT ")"
#define TT_RPAREN_AS_STR "rparen"

#define TT_LBRACKET 45  // [
#define TT_LBRACKET_TEXT "["
#define TT_LBRACKET_AS_STR "lbracket"

#define TT_RBRACKET 46 // ]
#define TT_RBRACKET_TEXT "]"
#define TT_RBRACKET_AS_STR "rbracket"

#define TT_LBRACE 47  // {
#define TT_LBRACE_TEXT "{"
#define TT_LBRACE_AS_STR "lbrace"

#define TT_RBRACE 48 // }
#define TT_RBRACE_TEXT "}"
#define TT_RBRACE_AS_STR "rbrace"

#define TT_COMMA 49  // ,
#define TT_COMMA_TEXT ","
#define TT_COMMA_AS_STR "comma"

#define TT_DOT 50 // .
#define TT_DOT_TEXT "."
#define TT_DOT_AS_STR "dot"

#define TT_LTMINUS 51 // <-
#define TT_LTMINUS_TEXT "<-"
#define TT_LTMINUS_AS_STR "ltminus"

#define TT_EQGT 52 // =>
#define TT_EQGT_TEXT "=>"
#define TT_EQGT_AS_STR "eqgt"


// keywords
#define TT_KW_PRINT 53
#define TT_KW_PRINT_TEXT "print"

#define TT_KW_PUT 54
#define TT_KW_PUT_TEXT "put"

#define TT_KW_IF 55
#define TT_KW_IF_TEXT "if"

#define TT_KW_ELSE 56
#define TT_KW_ELSE_TEXT "else"

#define TT_KW_ELIF 57
#define TT_KW_ELIF_TEXT "elif"

#define TT_KW_WHILE 58
#define TT_KW_WHILE_TEXT "while"

#define TT_KW_FOR 59
#define TT_KW_FOR_TEXT "for"

#define TT_KW_DO 60
#define TT_KW_DO_TEXT "do"

#define TT_KW_BREAK 61
#define TT_KW_BREAK_TEXT "break"

#define TT_KW_CONTINUE 62
#define TT_KW_CONTINUE_TEXT "continue"

#define TT_KW_DEF 63
#define TT_KW_DEF_TEXT "def"

#define TT_KW_RETURN 64
#define TT_KW_RETURN_TEXT "return"

#define TT_KW_USE 65
#define TT_KW_USE_TEXT "use"

#define TT_KW_END 66
#define TT_KW_END_TEXT "end"

#define TT_KW_IN 67
#define TT_KW_IN_TEXT "in"

#define TT_KW_MODE 68
#define TT_KW_MODE_TEXT "mode"

#define TT_KW_MATCH 69
#define TT_KW_MATCH_TEXT "match"

#define TT_KW_CASE 70
#define TT_KW_CASE_TEXT "case"

#define TT_KW_DEFAULT 71
#define TT_KW_DEFAULT_TEXT "default"

#define TT_KW_AND 72
#define TT_KW_AND_TEXT "and"

#define TT_KW_OR 73
#define TT_KW_OR_TEXT "or"

#define TT_KW_NOT 74
#define TT_KW_NOT_TEXT "not"

#define TT_KW_INCLUDE 75
#define TT_KW_INCLUDE_TEXT "include"

#define TT_KW_NEW 76
#define TT_KW_NEW_TEXT "new"

#define TT_KW_CLASS 77
#define TT_KW_CLASS_TEXT "class"

static const lets_str_t TokenTypeString[] = {
	TT_EOF_TEXT,

	TT_NUMBER_TEXT,
	TT_HEX_NUMBER_TEXT,
	TT_OCTAL_NUMBER_TEXT,
	TT_BINARY_NUMBER_TEXT,

	TT_IDENTIFIER_TEXT,
	TT_STRING_TEXT,

	TT_PLUS_AS_STR, // +
	TT_MINUS_AS_STR, // -
	TT_STAR_AS_STR, // *
	TT_SLASH_AS_STR, // /
	TT_PERCENT_AS_STR, // %
	TT_EQ_AS_STR, // =
	TT_EQEQ_AS_STR, // ==
	TT_EXCL_AS_STR, // !
	TT_EXCLEQ_AS_STR, // !=
	TT_LTEQ_AS_STR, // <=
	TT_LT_AS_STR, // <
	TT_GT_AS_STR, // >
	TT_GTEQ_AS_STR, // >=
	TT_PLUSEQ_AS_STR, // +=
	TT_MINUSEQ_AS_STR, // -=
	TT_STAREQ_AS_STR, // *=
	TT_SLASHEQ_AS_STR, // /=
	TT_PERCENTEQ_AS_STR, // %=
	TT_AMPEQ_AS_STR, // &=
	TT_CARETEQ_AS_STR, // ^=
	TT_BAREQ_AS_STR, // |=
	TT_PLUSPLUS_AS_STR, // ++
	TT_MINUSMINUS_AS_STR, // --
	TT_LTLT_AS_STR, // <<
	TT_GTGT_AS_STR, // >>
	TT_DOTDOT_AS_STR, // ..
	TT_STARSTAR_AS_STR, // **
	TT_TILDE_AS_STR, // ~
	TT_CARET_AS_STR, // ^
	TT_BAR_AS_STR, // |
	TT_BARBAR_AS_STR, // ||
	TT_AMP_AS_STR, // &
	TT_AMPAMP_AS_STR, // &&
	TT_QUESTION_AS_STR, // ?
	TT_COLON_AS_STR, // :
	TT_COLONCOLON_AS_STR, // ::
	TT_LPAREN_AS_STR, // (
	TT_RPAREN_AS_STR, // )
	TT_LBRACKET_AS_STR, // [
	TT_RBRACKET_AS_STR, // ]
	TT_LBRACE_AS_STR, // {
	TT_RBRACE_AS_STR, // }
	TT_COMMA_AS_STR, // ,
	TT_DOT_AS_STR, // .
	TT_LTMINUS_AS_STR, // <-
	TT_EQGT_AS_STR, // =>

	// keywords
	TT_KW_PRINT_TEXT,
	TT_KW_PUT_TEXT,
	TT_KW_IF_TEXT,
	TT_KW_ELSE_TEXT,
	TT_KW_ELIF_TEXT,
	TT_KW_WHILE_TEXT,
	TT_KW_FOR_TEXT,
	TT_KW_DO_TEXT,
	TT_KW_BREAK_TEXT,
	TT_KW_CONTINUE_TEXT,
	TT_KW_DEF_TEXT,
	TT_KW_RETURN_TEXT,
	TT_KW_USE_TEXT,
	TT_KW_END_TEXT,
	TT_KW_IN_TEXT,
	TT_KW_MODE_TEXT,
	TT_KW_MATCH_TEXT,
	TT_KW_CASE_TEXT,
	TT_KW_DEFAULT_TEXT,
	TT_KW_AND_TEXT,
	TT_KW_OR_TEXT,
	TT_KW_NOT_TEXT,
	TT_KW_INCLUDE_TEXT,
	TT_KW_NEW_TEXT,
	TT_KW_CLASS_TEXT,
};

#endif /* include__tokentype_h */
