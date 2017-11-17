//
//  include/e_in_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 08.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__e_in_expr_hpp
#define include__e_in_expr_hpp

#include <string>
#include <vector>
#include "main.h"
#include "expression.h"

class InExpression : virtual public Expression{
public:
    lets_vector_t<Expression*> expressions;
    Expression *container;
    
    InExpression(lets_vector_t<Expression*>, Expression*);
    Value* eval();
    lets_str_t to_s();
    ~InExpression();
};

#endif /* include__e_in_expr_hpp */

