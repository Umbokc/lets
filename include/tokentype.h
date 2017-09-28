#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H
#include <string>

enum TokenType {
	TT_NUMBER,
	TT_HEX_NUMBER,
	TT_OCTAL_NUMBER,
	TT_BINARY_NUMBER,
	TT_WORD,
	TT_TEXT,

	// keyword
	TT_PRINT,
	TT_INPUT,
	TT_PUT,
	TT_IF,
	TT_ELSE,
	TT_ELIF,
	TT_WHILE,
	TT_FOR,
	TT_DO,
	TT_BREAK,
	TT_CONTINUE,
	TT_DEF,
	TT_DEF_C,
	TT_RETURN,
	TT_USE,
	TT_END,
	TT_IN,

	TT_PLUS, // +
	TT_MINUS, // -
	TT_STAR, // *
	TT_SLASH, // /
	TT_PERCENT,// %
	TT_AT, // @

	TT_EQ, // =
	TT_EQEQ, // ==
	TT_EXCL, // !
	TT_EXCLEQ, // !=
	TT_LTEQ, // <=
	TT_LT, // <
	TT_GT, // >
	TT_GTEQ, // >=

	TT_PLUSEQ, // +=
	TT_MINUSEQ, // -=
	TT_STAREQ, // *=
	TT_SLASHEQ, // /=
	TT_PERCENTEQ, // %=
	TT_ATEQ, // @=
	TT_AMPEQ, // &=
	TT_CARETEQ, // ^=
	TT_BAREQ, // |=
	TT_COLONCOLONEQ, // ::=

	TT_PLUSPLUS, // ++
	TT_MINUSMINUS, // --

	TT_LTLT, // <<
	TT_GTGT, // >>

	TT_DOTDOT, // ..
	TT_STARSTAR, // **
	TT_QUESTIONCOLON, // ?:

	TT_TILDE, // ~
	TT_CARET, // ^
	TT_BAR, // |
	TT_BARBAR, // ||
	TT_AMP, // &
	TT_AMPAMP, // &&

	TT_QUESTION, // ?
	TT_COLON, // :
	TT_COLONCOLON, // ::

	TT_LPAREN,  // (
	TT_RPAREN, // )
	TT_LBRACKET,  // [
	TT_RBRACKET, // ]
	TT_LBRACE,  // {
	TT_RBRACE, // }
	TT_COMMA,  // ,
	TT_DOT, // .

	TT_EOF
};

static const std::string TokenTypeString[] = {
	"number",
	"hex number",
	"octal number",
	"binary number",
	"word",
	"text",

	// keyword
	"print",
	"input",
	"put",
	"if",
	"else",
	"elif",
	"while",
	"for",
	"do",
	"break",
	"continue",
	"def",
	"def_c",
	"return",
	"use",
	"end",
	"in",

	"plus", // +
	"minus", // -
	"star", // *
	"slash", // /
	"percent",// %
	"at", // @

	"eq", // =
	"eqeq", // ==
	"excl", // !
	"excleq", // !=
	"lteq", // <=
	"lt", // <
	"gt", // >
	"gteq", // >=

	"pluseq", // +=
	"minuseq", // -=
	"stareq", // *=
	"slasheq", // /=
	"percenteq", // %=
	"ateq", // @=
	"ampeq", // &=
	"careteq", // ^=
	"bareq", // |=
	"coloncoloneq", // ::=

	"plusplus", // ++
	"minusminus", // --

	"ltlt", // <<
	"gtgt", // >>

	"dotdot", // ..
	"starstar", // **
	"questioncolon", // ?:

	"tilde", // ~
	"caret", // ^
	"bar", // |
	"barbar", // ||
	"amp", // &
	"ampamp", // &&

	"question", // ?
	"colon", // :
	"coloncolon", // ::

	"lparen",  // (
	"rparen", // )
	"lbracket",  // [
	"rbracket", // ]
	"lbrace",  // {
	"rbrace", // }
	"comma",  // ,
	"dot", // .

	"eof"
};

const std::string TokenToString(int id) {
	return TokenTypeString[id];
}

#endif