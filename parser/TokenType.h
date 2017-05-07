#ifndef TOKENTYPE_H
#define TOKENTYPE_H
enum TokenType { 
	_NUMBER_,
	_HEX_NUMBER_,
	_WORD_,
	_TEXT_,

	// keyboard
	_PRINT_,
	_IF_,
	_ELSE_,
	_WHILE_,
	_FOR_,
	_DO_,
	_BREAK_,
	_CONTINUE_,
	_DEF_,
	_RETURN_,

	_PLUS_,
	_MINUS_,
	_STAR_,
	_SLASH_,
	_EQ_,
	_EQEQ_,
	_EXCL_,
	_EXCLEQ_,
	_LT_,
	_LTEQ_,
	_GT_,
	_GTEQ_,

	_BAR_,
	_BARBAR_,
	_AMP_,
	_AMPAMP_,

	_LPAREN_, // (
	_RPAREN_, // )
	_LBRACE_, // {
	_LBRACKET_, // ]
	_RBRACKET_, // [
	_RBRACE_, // }
	_COMMA_, // ,

	_EOF_
};

std::string TokenTypeText[] =  { 
	"_NUMBER_",
	"_HEX_NUMBER_",
	"_WORD_",
	"_TEXT_",

	"_PRINT_",
	"_IF_",
	"_ELSE_",
	"_WHILE_",
	"_FOR_",
	"_DO_",
	"_BREAK_",
	"_CONTINUE_",
	"_DEF_",
	"_RETURN_",

	"_PLUS_",
	"_MINUS_",
	"_STAR_",
	"_SLASH_",
	"_EQ_",
	"_EQEQ_",
	"_EXCL_",
	"_EXCLEQ_",
	"_LT_",
	"_LTEQ_",
	"_GT_",
	"_GTEQ_",

	"_BAR_",
	"_BARBAR_",
	"_AMP_",
	"_AMPAMP_",

	"_LPAREN_", // (
	"_RPAREN_", // )
	"_LBRACE_", // {
	"_LBRACKET_", // ]
	"_RBRACKET_", // [
	"_RBRACE_", // }
	"_COMMA_", // ,

	"_EOF_"
};

#endif