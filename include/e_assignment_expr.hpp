//
//  e_assignment_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__expr__assignment_expr_hpp
#define ast__expr__assignment_expr_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"
#include "accessible.h"
#include "l_function.h"

#include "e_binary_expr.hpp"

class AssignmentExpression : virtual public Expression, virtual public Statement{
public:
    NS_Binary::Operator operation;
    Accessible *target;
    Expression *expression;
    
    AssignmentExpression(NS_Binary::Operator, Accessible*, Expression*);
    void execute();
    Value* eval();
    lets_str_t to_s();
    ~AssignmentExpression();
};

#endif /* ast__expr__assignment_expr_hpp */
