//
//  e_unary_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef e_unary_expr_hpp
#define e_unary_expr_hpp

#include <string>
#include "main.h"
#include "expression.h"
#include "statement.h"

namespace NS_Unary{
    
    static enum Operator{
        INCREMENT_PREFIX, // ++
        DECREMENT_PREFIX, // --
        INCREMENT_POSTFIX, // ++
        DECREMENT_POSTFIX, // --
        NEGATE, // -
        // Boolean
        NOT, // !
        // Bitwise
        COMPLEMENT, // ~
    } x;
    
    const static lets_str_t OperatorString[] = {
        "++",
        "--",
        "++",
        "--",
        "-",
        // Boolean
        "!",
        // Bitwise
        "~",
    };
}

class UnaryExpression : public Expression, public Statement{
public:
    
    NS_Unary::Operator operation;
    Expression *expr;
    
    UnaryExpression(NS_Unary::Operator,Expression*);
    
    void execute();
    
    Value *eval();
    
    Value *UE_increment(Value*);
    Value *UE_decrement(Value*);
    Value *UE_complement(Value*);
    Value *UE_negate(Value*);
    Value *UE_not(Value*);
    
    lets_str_t to_s();
    
    ~UnaryExpression();
private:
    lets_str_t reverse(const lets_str_t& the);
    
    template<class BidirIt>
    void reverse(BidirIt first, BidirIt last){
        while ((first != last) && (first != --last)) {
            std::swap(*first++, *last);
        }
    }
};

#endif /* e_unary_expr_hpp */
