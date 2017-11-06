//
//  ex_parse.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef exceptions__parse_h
#define exceptions__parse_h

#include <string>
#include "main.h"

class ParseException {
protected:
    lets_str_t message;
public:
    
    ParseException(){}
    
    ParseException(lets_str_t message):message(std::move(message)){}
    lets_str_t get_message(){ return message; }
    
    ~ParseException(){}
    
};

#endif /* exceptions__parse_h */
