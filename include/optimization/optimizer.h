//
//  optimization/optimizer.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef optimization__optimizer_h
#define optimization__optimizer_h

#include "../statement.h"

class Optimizer {
public:
	static Statement* optimize(Statement*, int, bool);
};

#endif /* optimization__optimizer_h */

