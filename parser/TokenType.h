#ifndef TOKENTYPE_H
#define TOKENTYPE_H
enum TokenType { 
	_NUMBER_, _HEX_NUMBER_, _WORD_,	_TEXT_,

	// keyword
	_PRINT_, 
	_IF_, _ELSE_, 
	_WHILE_, _FOR_, _DO_, 
	_BREAK_, _CONTINUE_, 
	_DEF_, _RETURN_,
	_USE_,

	_PLUS_, // +
	_MINUS_, // -
	_STAR_, // *
	_SLASH_, // /
	_PERCENT_,// %
	_EQ_, // =
	_EQEQ_, // ==
	_EXCL_, // !
	_EXCLEQ_, // !=
	_LTEQ_, // <=
	_LT_, // <
	_GT_, // >
	_GTEQ_, // >=

	_LTLT_, // <<
	_GTGT_, // >>
	_GTGTGT_, // >>>

	_TILDE_, // ~
	_CARET_, // ^
	_BAR_, // |
	_BARBAR_, // ||
	_AMP_, // &
	_AMPAMP_, // &&

	_QUESTION_, // ?
	_COLON_, // :

	_LPAREN_, // (
	_RPAREN_, // )
	_LBRACKET_, // [
	_RBRACKET_, // ]
	_LBRACE_, // {
	_RBRACE_, // }
	_COMMA_, // ,

	_EOF_
};

std::string TokenTypeText[] =  { 
	"_NUMBER_", "_HEX_NUMBER_", "_WORD_",	"_TEXT_",

	// keyword
	"_PRINT_",
	"_IF_", "_ELSE_",
	"_WHILE_", "_FOR_", "_DO_", 
	"_BREAK_", "_CONTINUE_",
	"_DEF_", "_RETURN_",
	"_USE_",

	"_PLUS_ \"+\"", // +
	"_MINUS_ \"-\"", // -
	"_STAR_ \"*\"", // *
	"_SLASH_ \"/\"", // /
	"_PERCENT_",// %
	"_EQ_ \"=\"", // =
	"_EQEQ_ \"==\"", // ==
	"_EXCL_ \"!\"", // !
	"_EXCLEQ_ \"!=\"", // !=
	"_LTEQ_ \"<=\"", // <=
	"_LT_ \"<\"", // <
	"_GT_ \">\"", // >
	"_GTEQ_ \">=\"", // >=

	"_LTLT_ \"<<\"", // <<
	"_GTGT_ \">>\"", // >>
	"_GTGTGT_ \">>>\"", // >>>

	"_TILDE_ \"~\"", // ~
	"_CARET_ \"^\"", // ^
	"_BAR_ \"|\"", // |
	"_BARBAR_ \"||\"", // ||
	"_AMP_ \"&\"", // &
	"_AMPAMP_ \"&&\"", // &&

	"_QUESTION_ \"?\"", // ?
	"_COLON_ \":\"", // :

	"_LPAREN_ \"(\"", // (
	"_RPAREN_ \")\"", // )
	"_LBRACKET_ \"[\"", // [
	"_RBRACKET_ \"]\"", // ]
	"_LBRACE_ \"{\"", // {
	"_RBRACE_ \"}\"", // }
	"_COMMA_ \",\"", // ,

	"_EOF_"
};

#endif