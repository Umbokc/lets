//
//  accessible.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__accessible_h
#define ast__accessible_h

#include "main.h"
#include "node.h"
#include "l_value.h"

class Accessible : virtual public Node {
public:
    virtual Value* get() = 0;
    virtual Value* set(Value* value) = 0;
    virtual lets_str_t to_s() = 0;
};


#endif /* ast__accessible_h */
