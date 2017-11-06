//
//  s_if_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_if_stat_hpp
#define s_if_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class IfStatement : virtual public Statement{
public:
    Expression *expression;
    Statement *if_statement;
    Statement *else_statement;
    
    IfStatement(Expression *, Statement *, Statement *);
    
    void execute();
    
    lets_str_t to_s();
    
    ~IfStatement();
};

#endif /* s_if_stat_hpp */
