//
//  e_value_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__expr__value_expr_hpp
#define ast__expr__value_expr_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "l_function.h"

class ValueExpression : virtual public Expression {
public:
    Value *value;
    
    ValueExpression();
    
    ValueExpression(int);
    ValueExpression(double);
    ValueExpression(long);
    
    ValueExpression(lets_str_t);
    ValueExpression(Function*);
    ValueExpression(Value*);
    
    Value *eval();

    
    lets_str_t to_s();
    
    ~ValueExpression();
};

#endif /* ast__expr__value_expr_hpp */
