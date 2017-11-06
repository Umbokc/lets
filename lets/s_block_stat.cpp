//
//  block_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/s_block_stat.hpp"

BlockStatement::BlockStatement(){}

void BlockStatement::add(Statement *statement){
    statements.push_back(statement);
}

void BlockStatement::execute(){
    for(auto st : statements){
        st->execute();
    }
    
}

//void accept(Visitor *visitor){
//    visitor->visit(this);
//}
//
//Node * accept_r(ResultVisitor* visitor){
//    return visitor->visit(this);
//}
//
//template<typename T> Node* accept_r_a(ResultVisitorWithArg<T>* visitor, T t){
//    return visitor->visit(this, t);
//}

lets_str_t BlockStatement::to_s(){
    lets_str_t result = "";
    
    for(auto st : statements){
        result += st->to_s();
        result.push_back('\n');
    }
    
    return result;
}
