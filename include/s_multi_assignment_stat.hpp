//
//  s_multi_assignment_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 15.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__s_multi_assignment_stat_hpp
#define ast__s_multi_assignment_stat_hpp

#include <string>
#include <vector>
#include "main.h"
#include "expression.h"
#include "statement.h"
#include "accessible.h"

class MultiAssignmentStatement : virtual public Statement{
public:
    lets_vector_t<Accessible*> targets;
    Expression *expression;
    
    MultiAssignmentStatement(lets_vector_t<Accessible*>, Expression*);
    void execute();
    lets_str_t to_s();
    ~MultiAssignmentStatement();
};

#endif /* ast__s_multi_assignment_stat_hpp */
