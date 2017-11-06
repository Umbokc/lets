//
//  s_do_while_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_do_while_stat_hpp
#define s_do_while_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class DoWhileStatement : virtual public Statement{
public:
    Expression *condition;
    Statement *statement;
    
    DoWhileStatement(Expression*,Statement*);
    
    void execute();

    
    lets_str_t to_s();
    
    ~DoWhileStatement();
};

#endif /* s_do_while_stat_hpp */
