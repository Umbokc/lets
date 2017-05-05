#ifndef TOKENTYPE
#define TOKENTYPE
enum TokenType { 
	_NUMBER_,
	_HEX_NUMBER_,
	_WORD_,
	_TEXT_,

	_PRINT_,

	_PLUS_,
	_MINUS_,
	_STAR_,
	_SLASH_,

	_EQ_,

	_LPAREN_, // (
	_RPAREN_, // )

	_EOF_
};

std::string TokenTypeText[] =  { 
	"_NUMBER_",
	"_HEX_NUMBER_",
	"_WORD_",
	"_TEXT_",

	"_PRINT_",

	"_PLUS_",
	"_MINUS_",
	"_STAR_",
	"_SLASH_",

	"_EQ_",

	"_LPAREN_", // (
	"_RPAREN_", // )

	"_EOF_"
};

#endif