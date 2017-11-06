//
//  s_put_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef s_put_stat_hpp
#define s_put_stat_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

class PutStatement : virtual public Statement{
public:
    Expression *expression;
    
    PutStatement(Expression *);
    
    void execute();
    
    lets_str_t to_s();
    
    ~PutStatement();
};


#endif /* s_put_stat_hpp */
