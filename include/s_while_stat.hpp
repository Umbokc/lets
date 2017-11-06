//
//  s_while_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_while_stat_hpp
#define s_while_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class WhileStatement : virtual public Statement{
public:
    Expression *condition;
    Statement *statement;
    
    WhileStatement(Expression *, Statement *);
    
    void execute();
    
    lets_str_t to_s();
    
    ~WhileStatement();
};


#endif /* s_while_stat_hpp */
