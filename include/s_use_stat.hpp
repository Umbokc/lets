//
//  s_use_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_use_stat_hpp
#define s_use_stat_hpp

#include <string>
#include "main.h"
#include "e_array_expr.hpp"
#include "statement.h"

class UseStatement : virtual public Statement{
public:

    Expression *expression;
    Expression *elements;
    
    UseStatement(Expression*);
    UseStatement(Expression*, Expression*);
    
    void execute();
    
    lets_str_t to_s();
    
    ~UseStatement();
};

#endif /* s_use_stat_hpp */
