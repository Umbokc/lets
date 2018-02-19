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

#define TT_MINUS 8 // -
#define TT_MINUS_TEXT "-"

#define TT_STAR 9 // *
#define TT_STAR_TEXT "*"

#define TT_SLASH 10 // /
#define TT_SLASH_TEXT "/"

#define TT_BACKSLASH 11 // '\'
#define TT_BACKSLASH_TEXT "\\"

#define TT_PERCENT 12 // %
#define TT_PERCENT_TEXT "%"

#define TT_EQ 13 // =
#define TT_EQ_TEXT "="

#define TT_EQEQ 14 // ==
#define TT_EQEQ_TEXT "=="

#define TT_EXCL 15 // !
#define TT_EXCL_TEXT "!"

#define TT_EXCLEQ 16 // !=
#define TT_EXCLEQ_TEXT "!="

#define TT_LTEQ 17 // <=
#define TT_LTEQ_TEXT "<="

#define TT_LT 18 // <
#define TT_LT_TEXT "<"

#define TT_GT 19 // >
#define TT_GT_TEXT ">"

#define TT_GTEQ 20 // >=
#define TT_GTEQ_TEXT ">="

#define TT_PLUSEQ 21 // +=
#define TT_PLUSEQ_TEXT "+="

#define TT_MINUSEQ 22 // -=
#define TT_MINUSEQ_TEXT "-="

#define TT_STAREQ 23 // *=
#define TT_STAREQ_TEXT "*="

#define TT_SLASHEQ 24 // /=
#define TT_SLASHEQ_TEXT "/="

#define TT_PERCENTEQ 25 // %=
#define TT_PERCENTEQ_TEXT "%="

#define TT_AMPEQ 26 // &=
#define TT_AMPEQ_TEXT "&="

#define TT_CARETEQ 27 // ^=
#define TT_CARETEQ_TEXT "^="

#define TT_BAREQ 28 // |=
#define TT_BAREQ_TEXT "|="

#define TT_PLUSPLUS 29 // ++
#define TT_PLUSPLUS_TEXT "++"

#define TT_MINUSMINUS 30 // --
#define TT_MINUSMINUS_TEXT "--"

#define TT_LTLT 31 // <<
#define TT_LTLT_TEXT "<<"

#define TT_GTGT 32 // >>
#define TT_GTGT_TEXT ">>"

#define TT_DOTDOT 33 // ..
#define TT_DOTDOT_TEXT ".."

#define TT_STARSTAR 34 // **
#define TT_STARSTAR_TEXT "**"

#define TT_TILDE 35 // ~
#define TT_TILDE_TEXT "~"

#define TT_CARET 36 // ^
#define TT_CARET_TEXT "^"

#define TT_BAR 37 // |
#define TT_BAR_TEXT "|"

#define TT_BARBAR 38 // ||
#define TT_BARBAR_TEXT "||"

#define TT_AMP 39 // &
#define TT_AMP_TEXT "&"

#define TT_AMPAMP 40 // &&
#define TT_AMPAMP_TEXT "&&"

#define TT_QUESTION 41 // ?
#define TT_QUESTION_TEXT "?"

#define TT_COLON 42 // :
#define TT_COLON_TEXT ":"

#define TT_COLONCOLON 43 // ::
#define TT_COLONCOLON_TEXT "::"

#define TT_LPAREN 44  // (
#define TT_LPAREN_TEXT "("

#define TT_RPAREN 45 // )
#define TT_RPAREN_TEXT ")"

#define TT_LBRACKET 46  // [
#define TT_LBRACKET_TEXT "["

#define TT_RBRACKET 47 // ]
#define TT_RBRACKET_TEXT "]"

#define TT_LBRACE 48  // {
#define TT_LBRACE_TEXT "{"

#define TT_RBRACE 49 // }
#define TT_RBRACE_TEXT "}"

#define TT_COMMA 50  // ,
#define TT_COMMA_TEXT ","

#define TT_DOT 51 // .
#define TT_DOT_TEXT "."

#define TT_LTMINUS 52 // <-
#define TT_LTMINUS_TEXT "<-"

#define TT_EQGT 53 // =>
#define TT_EQGT_TEXT "=>"


// keywords
#define TT_KW_PRINT 54
#define TT_KW_PRINT_TEXT "print"

#define TT_KW_PUT 55
#define TT_KW_PUT_TEXT "put"

#define TT_KW_IF 56
#define TT_KW_IF_TEXT "if"

#define TT_KW_ELSE 57
#define TT_KW_ELSE_TEXT "else"

#define TT_KW_ELIF 58
#define TT_KW_ELIF_TEXT "elif"

#define TT_KW_WHILE 59
#define TT_KW_WHILE_TEXT "while"

#define TT_KW_FOR 60
#define TT_KW_FOR_TEXT "for"

#define TT_KW_DO 61
#define TT_KW_DO_TEXT "do"

#define TT_KW_BREAK 62
#define TT_KW_BREAK_TEXT "break"

#define TT_KW_CONTINUE 63
#define TT_KW_CONTINUE_TEXT "continue"

#define TT_KW_DEF 64
#define TT_KW_DEF_TEXT "def"

#define TT_KW_RETURN 65
#define TT_KW_RETURN_TEXT "return"

#define TT_KW_USE 66
#define TT_KW_USE_TEXT "use"

#define TT_KW_END 67
#define TT_KW_END_TEXT "end"

#define TT_KW_IN 68
#define TT_KW_IN_TEXT "in"

#define TT_KW_MODE 69
#define TT_KW_MODE_TEXT "mode"

#define TT_KW_MATCH 70
#define TT_KW_MATCH_TEXT "match"

#define TT_KW_CASE 71
#define TT_KW_CASE_TEXT "case"

#define TT_KW_DEFAULT 72
#define TT_KW_DEFAULT_TEXT "default"

#define TT_KW_AND 73
#define TT_KW_AND_TEXT "and"

#define TT_KW_OR 74
#define TT_KW_OR_TEXT "or"

#define TT_KW_NOT 75
#define TT_KW_NOT_TEXT "not"

#define TT_KW_INCLUDE 76
#define TT_KW_INCLUDE_TEXT "include"

#define TT_KW_NEW 77
#define TT_KW_NEW_TEXT "new"

#define TT_KW_CLASS 78
#define TT_KW_CLASS_TEXT "class"

#define TOKEN_TO_STRING(TYPE, TEXT) \
	("< " + TokenTypeString[TYPE][0] + " : " + (TEXT == "" ? TokenTypeString[TYPE][1] : TEXT) + " >")

static const lets_str_t TokenTypeString[][2] = {
	{TT_EOF_TEXT, ""},

	{TT_NUMBER_TEXT, ""},
	{TT_HEX_NUMBER_TEXT, ""},
	{TT_OCTAL_NUMBER_TEXT, ""},
	{TT_BINARY_NUMBER_TEXT, ""},

	{TT_IDENTIFIER_TEXT, ""},
	{TT_STRING_TEXT, ""},

	{"plus", TT_PLUS_TEXT}, // +
	{"minus", TT_MINUS_TEXT}, // -
	{"star", TT_STAR_TEXT}, // *
	{"slash", TT_SLASH_TEXT}, // /
	{"backslash", TT_BACKSLASH_TEXT}, // '\'
	{"percent", TT_PERCENT_TEXT}, // %
	{"eq", TT_EQ_TEXT}, // =
	{"eqeq", TT_EQEQ_TEXT}, // ==
	{"excl", TT_EXCL_TEXT}, // !
	{"excleq", TT_EXCLEQ_TEXT}, // !=
	{"lteq", TT_LTEQ_TEXT}, // <=
	{"lt", TT_LT_TEXT}, // <
	{"gt", TT_GT_TEXT}, // >
	{"gteq", TT_GTEQ_TEXT}, // >=
	{"pluseq", TT_PLUSEQ_TEXT}, // +=
	{"minuseq", TT_MINUSEQ_TEXT}, // -=
	{"stareq", TT_STAREQ_TEXT}, // *=
	{"slasheq", TT_SLASHEQ_TEXT}, // /=
	{"percenteq", TT_PERCENTEQ_TEXT}, // %=
	{"ampeq", TT_AMPEQ_TEXT}, // &=
	{"careteq", TT_CARETEQ_TEXT}, // ^=
	{"bareq", TT_BAREQ_TEXT}, // |=
	{"plusplus", TT_PLUSPLUS_TEXT}, // ++
	{"minusminus", TT_MINUSMINUS_TEXT}, // --
	{"ltlt", TT_LTLT_TEXT}, // <<
	{"gtgt", TT_GTGT_TEXT}, // >>
	{"dotdot", TT_DOTDOT_TEXT}, // ..
	{"starstar", TT_STARSTAR_TEXT}, // **
	{"tilde", TT_TILDE_TEXT}, // ~
	{"caret", TT_CARET_TEXT}, // ^
	{"bar", TT_BAR_TEXT}, // |
	{"barbar", TT_BARBAR_TEXT}, // ||
	{"amp", TT_AMP_TEXT}, // &
	{"ampamp", TT_AMPAMP_TEXT}, // &&
	{"question", TT_QUESTION_TEXT}, // ?
	{"colon", TT_COLON_TEXT}, // :
	{"coloncolon", TT_COLONCOLON_TEXT}, // ::
	{"lparen", TT_LPAREN_TEXT}, // (
	{"rparen", TT_RPAREN_TEXT}, // )
	{"lbracket", TT_LBRACKET_TEXT}, // [
	{"rbracket", TT_RBRACKET_TEXT}, // ]
	{"lbrace", TT_LBRACE_TEXT}, // {
	{"rbrace", TT_RBRACE_TEXT}, // }
	{"comma", TT_COMMA_TEXT}, // ,
	{"dot", TT_DOT_TEXT}, // .
	{"ltminus", TT_LTMINUS_TEXT}, // <-
	{"eqgt", TT_EQGT_TEXT}, // =>

	// keywords
	{TT_KW_PRINT_TEXT, ""},
	{TT_KW_PUT_TEXT, ""},
	{TT_KW_IF_TEXT, ""},
	{TT_KW_ELSE_TEXT, ""},
	{TT_KW_ELIF_TEXT, ""},
	{TT_KW_WHILE_TEXT, ""},
	{TT_KW_FOR_TEXT, ""},
	{TT_KW_DO_TEXT, ""},
	{TT_KW_BREAK_TEXT, ""},
	{TT_KW_CONTINUE_TEXT, ""},
	{TT_KW_DEF_TEXT, ""},
	{TT_KW_RETURN_TEXT, ""},
	{TT_KW_USE_TEXT, ""},
	{TT_KW_END_TEXT, ""},
	{TT_KW_IN_TEXT, ""},
	{TT_KW_MODE_TEXT, ""},
	{TT_KW_MATCH_TEXT, ""},
	{TT_KW_CASE_TEXT, ""},
	{TT_KW_DEFAULT_TEXT, ""},
	{TT_KW_AND_TEXT, ""},
	{TT_KW_OR_TEXT, ""},
	{TT_KW_NOT_TEXT, ""},
	{TT_KW_INCLUDE_TEXT, ""},
	{TT_KW_NEW_TEXT, ""},
	{TT_KW_CLASS_TEXT, ""},
};

#endif /* include__tokentype_h */
