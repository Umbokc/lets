//
//  s_assignment_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_assignment_stat_hpp
#define s_assignment_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class AssignmentStatement : virtual public Statement{
public:
    lets_str_t variable;
    Expression* expression;
    
    AssignmentStatement(lets_str_t, Expression*);
    
    void execute();
    
    lets_str_t to_s();
    
    ~AssignmentStatement();
};

#endif /* s_assignment_stat_hpp */
