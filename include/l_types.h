//
//  l_types.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lib__types_h
#define lib__types_h

#include <string>
#include "main.h"

enum Types {
    T_NUMBER,
    T_STRING,
    T_ARRAY,
    T_MAP,
    T_FUNCTION,
    
    T_REGEXP,
    T_MODULE,
    T_CLASS,
    T_INTERFACE,
    T_OBJECT,
    T_FILE,
};

const lets_str_t TypesString[] = {
    "number",
    "string",
    "array",
    "map",
    "function",
    
    "regexp",
    "module",
    "class",
    "interface",
    "object",
    "file",
};

#endif /* lib__types_h */
