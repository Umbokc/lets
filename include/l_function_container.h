//
//  l_function_container.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lib__function_container_h
#define lib__function_container_h

#include "l_function.h"

class FunctionContainer {
private:
public:
    Function* body;
    bool is_constant;
    
    FunctionContainer(Function *body) : body(std::move(body)) {
        is_constant = false;
    }
    
    FunctionContainer(Function *body, bool is_const):
    body(std::move(body)), is_constant(std::move(is_const)){}
    
    ~FunctionContainer(){}
    
};

#endif /* lib__function_container_h */
