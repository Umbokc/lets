//
//  block_stat.hpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef block_stat_hpp
#define block_stat_hpp

#include <string>
#include <vector>
#include "main.h"
#include "statement.h"


class BlockStatement : virtual public Statement {
public:
    
    lets_vector_t<Statement*> statements;
    
    BlockStatement();
    
    void add(Statement*);
    
    void execute();
    
//    void accept(Visitor *visitor){
//        visitor->visit(this);
//    }
    
//    Node * accept_r(ResultVisitor* visitor){
//        return visitor->visit(this);
//    }
    
//    template<typename T> Node* accept_r_a(ResultVisitorWithArg<T>* visitor, T t){
//        return visitor->visit(this, t);
//    }
    
    lets_str_t to_s();
};


#endif /* block_stat_hpp */
