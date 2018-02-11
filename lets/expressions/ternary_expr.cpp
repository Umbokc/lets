//
//  lets/expressions/ternary_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/ternary_expr.hpp"

TernaryExpression::TernaryExpression(Expression *condition,Expression *trueExpr,Expression *falseExpr):
condition(std::move(condition)), trueExpr(std::move(trueExpr)), falseExpr(std::move(falseExpr)){}

Value* TernaryExpression::eval(){
    if (condition->eval()->as_number() != 0) {
        return trueExpr->eval();
    } else {
        return falseExpr->eval();
    }
}

lets_str_t TernaryExpression::to_s(){
    return condition->to_s() + " ? " + trueExpr->to_s() + " : " + falseExpr->to_s();
}

TernaryExpression::~TernaryExpression(){

}
