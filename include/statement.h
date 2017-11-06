//
//  statement.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef ast__statement_h
#define ast__statement_h

#include "main.h"
#include "node.h"

class Statement : virtual public Node {
public:
    virtual void execute() = 0;
    virtual lets_str_t to_s() = 0;
};


#endif /* statement_h */
