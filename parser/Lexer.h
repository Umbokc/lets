#ifndef LEXER_H
#define LEXER_H

static std::string OPERATOR_CHARS = "+-*/%()[]{}=<>!&|,^~?:";
static std::map<std::string, TokenType> OPERATORS = {
	{"+", _PLUS_},
	{"-", _MINUS_},
	{"*", _STAR_},
	{"/", _SLASH_},
	{"%", _PERCENT_},
	{"(", _LPAREN_},
	{")", _RPAREN_},
	{"[", _LBRACKET_},
	{"]", _RBRACKET_},
	{"{", _LBRACE_},
	{"}", _RBRACE_},
	{"=", _EQ_},
	{"<", _LT_},
	{">", _GT_},
	{",", _COMMA_},
	{"^", _CARET_},
	{"~", _TILDE_},
	{"?", _QUESTION_},
	{":", _COLON_},

	{"!", _EXCL_},
	{"&", _AMP_},
	{"|", _BAR_},

	{"==", _EQEQ_},
	{"!=", _EXCLEQ_},
	{"<=", _LTEQ_},
	{">=", _GTEQ_},

	{"&&", _AMPAMP_},
	{"||", _BARBAR_},

	{"<<", _LTLT_},
	{">>", _GTGT_},
	{">>>", _GTGTGT_},
};

#include "Lexer.cpp"

#endif