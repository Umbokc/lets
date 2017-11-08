//
//  ex_pattern_matching.h
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ex_pattern_matching_h
#define ex_pattern_matching_h

#include "ex_parse.h"

class PatternMatchingException : public ParseException {
public:
    PatternMatchingException(){}
    PatternMatchingException(lets_str_t message): ParseException(message){}
    ~PatternMatchingException(){}
    
};

#endif /* ex_pattern_matching_h */