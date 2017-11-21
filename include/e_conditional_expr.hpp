//
//  e_conditional_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef e_conditional_expr_hpp
#define e_conditional_expr_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "e_binary_expr.hpp"

namespace NS_Conditional{
    typedef enum {EQUALS, NOT_EQUALS, LT, LTEQ, GT, GTEQ, AND, OR } Operator;
    static const lets_str_t OperatorString[] =  { "==", "!=", "<", "<=", ">", ">=", "&&", "||" };
}

class ConditionalExpression : public Expression{
public:
    
    NS_Conditional::Operator operation;
    Expression *expr1;
    Expression *expr2;
    
    
    ConditionalExpression(NS_Conditional::Operator, Expression*, Expression*);
    
    Value* eval();
    Value* eval_and_or(Value*&, bool);
    
    lets_str_t to_s();
    
    ~ConditionalExpression();
};

#endif /* e_conditional_expr_hpp */
