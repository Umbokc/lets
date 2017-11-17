//
//  tokentype.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef tokentype_h
#define tokentype_h

#define TT_EOF 0

#define TT_NUMBER 1
#define TT_HEX_NUMBER 2
#define TT_OCTAL_NUMBER 3
#define TT_BINARY_NUMBER 4

#define TT_IDENTIFIER 5
#define TT_STRING 6

#define TT_PLUS 7 // +
#define TT_MINUS 8 // -
#define TT_STAR 9 // *
#define TT_SLASH 10 // /
#define TT_PERCENT 11 // %
#define TT_AT 12 // @
#define TT_EQ 13 // =
#define TT_EQEQ 14 // ==
#define TT_EXCL 15 // !
#define TT_EXCLEQ 16 // !=
#define TT_LTEQ 17 // <=
#define TT_LT 18 // <
#define TT_GT 19 // >
#define TT_GTEQ 20 // >=
#define TT_PLUSEQ 21 // +=
#define TT_MINUSEQ 22 // -=
#define TT_STAREQ 23 // *=
#define TT_SLASHEQ 24 // /=
#define TT_PERCENTEQ 25 // %=
#define TT_AMPEQ 26 // &=
#define TT_CARETEQ 27 // ^=
#define TT_BAREQ 28 // |=
#define TT_PLUSPLUS 29 // ++
#define TT_MINUSMINUS 30 // --
#define TT_LTLT 31 // <<
#define TT_GTGT 32 // >>
#define TT_DOTDOT 33 // ..
#define TT_STARSTAR 34 // **
#define TT_TILDE 35 // ~
#define TT_CARET 36 // ^
#define TT_BAR 37 // |
#define TT_BARBAR 38 // ||
#define TT_AMP 39 // &
#define TT_AMPAMP 40 // &&
#define TT_QUESTION 41 // ?
#define TT_COLON 42 // :
#define TT_COLONCOLON 43 // ::
#define TT_LPAREN 44  // (
#define TT_RPAREN 45 // )
#define TT_LBRACKET 46  // [
#define TT_RBRACKET 47 // ]
#define TT_LBRACE 48  // {
#define TT_RBRACE 49 // }
#define TT_COMMA 50  // ,
#define TT_DOT 51 // .
#define TT_LTMINUS 52 // <-
#define TT_EQGT 53 // =>

// keywords
#define TT_KW_PRINT 54
#define TT_KW_PUT 55
#define TT_KW_IF 56
#define TT_KW_ELSE 57
#define TT_KW_ELIF 58
#define TT_KW_WHILE 59
#define TT_KW_FOR 60
#define TT_KW_DO 61
#define TT_KW_BREAK 62
#define TT_KW_CONTINUE 63
#define TT_KW_DEF 64
#define TT_KW_DEF_C 65
#define TT_KW_RETURN 66
#define TT_KW_USE 67
#define TT_KW_END 68
#define TT_KW_IN 69
#define TT_KW_MODE 70
#define TT_KW_SELF 71
#define TT_KW_MATCH 72
#define TT_KW_CASE 73
#define TT_KW_DEFAULT 74
#define TT_KW_AND 75
#define TT_KW_OR 76
#define TT_KW_NOT 77

static const lets_str_t TokenTypeString[] = {
    "eof",

    "number",
    "hex_number",
    "octal_number",
    "binary_number",

    "identifier",
    "string",

    "plus", // +
    "minus", // -
    "star", // *
    "slash", // /
    "percent", // %
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
    "ampeq", // &=
    "careteq", // ^=
    "bareq", // |=
    "plusplus", // ++
    "minusminus", // --
    "ltlt", // <<
    "gtgt", // >>
    "dotdot", // ..
    "starstar", // **
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
    "ltminus", // <-
    "eqgt", // =>

    // keywords
    "print",
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
    "mode",
    "self",
    "match",
    "case",
    "default",
    "and",
    "or",
    "not",
};
#endif /* tokentype_h */
