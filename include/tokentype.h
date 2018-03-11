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
#define TT_NUMBER 1
#define TT_HEX_NUMBER 2
#define TT_OCTAL_NUMBER 3
#define TT_BINARY_NUMBER 4
#define TT_IDENTIFIER 5
#define TT_STRING 6
#define TT_OPERATOR 7
#define TT_KEYWORD 8

#define TOKEN_TO_STRING(TYPE, TEXT) \
	("< " + TokenTypeString[TYPE] + " : " + (TEXT == "" ? TokenTypeString[TYPE] : TEXT) + " >")

static const lets_str_t TokenTypeString[] = {
	"eof",
	"number",
	"hex_number",
	"octal_number",
	"binary_number",
	"identifier",
	"string",
	"operator",
	"keyword",
};

#endif /* include__tokentype_h */
