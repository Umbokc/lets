//
//  s_array_assignment_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_array_assignment_stat_hpp
#define s_array_assignment_stat_hpp

#include <string>
#include "main.h"
#include "e_array_access_expr.hpp"
#include "statement.h"

class ArrayAssignmentStatement : virtual public Statement{
public:
    Expression *expression;
    ArrayAccessExpression *array;
    
    ArrayAssignmentStatement(ArrayAccessExpression *, Expression *);
    
    void execute();
    
    lets_str_t to_s();
    
    ~ArrayAssignmentStatement();
};

#endif /* s_array_assignment_stat_hpp */
