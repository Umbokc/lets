//
//  expression.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__expression_h
#define ast__expression_h

#include "main.h"
#include "node.h"
#include "l_value.h"

class Expression : virtual public Node {
public:
    virtual Value *eval() = 0;
    virtual lets_str_t to_s() = 0;
};

#endif /* ast__expression_h */
