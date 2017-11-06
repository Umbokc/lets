//
//  e_array_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__expr__array_expr_hpp
#define ast__expr__array_expr_hpp

#include <string>
#include <vector>
#include "main.h"
#include "expression.h"

class ArrayExpression : public Expression{
public:
    lets_vector_t<Expression *> elements;
    
    ArrayExpression(lets_vector_t<Expression *> elements);
    Value *eval();
    lets_str_t to_s();
    ~ArrayExpression();
};


#endif /* ast__expr__array_expr_hpp */
