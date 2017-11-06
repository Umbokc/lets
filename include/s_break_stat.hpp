//
//  s_break_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_break_stat_hpp
#define s_break_stat_hpp

#include <string>
#include "main.h"
#include "statement.h"

class BreakStatement : virtual public Statement{
public:
    
    BreakStatement();
    
    void execute();
    
    lets_str_t to_s();
    
    ~BreakStatement();
};

#endif /* s_break_stat_hpp */
