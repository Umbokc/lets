//
//  e_variable_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef e_variable_expr_hpp
#define e_variable_expr_hpp

#include <string>
#include <vector>
#include "main.h"
#include "expression.h"
#include "accessible.h"

class VariableExpression : virtual public Expression, virtual public Accessible{
public:
    
    mutable lets_str_t name;
    
    VariableExpression(lets_str_t);
    
    Value* eval();
    Value* get();
    Value* set(Value*);
    
    lets_str_t to_s();
    
    ~VariableExpression();
};

#endif /* e_variable_expr_hpp */
