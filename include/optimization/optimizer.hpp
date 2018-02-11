//
//  include/optimization/optimizer.hpp
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__optimization__optimizer_hpp
#define include__optimization__optimizer_hpp

#include "../statement.h"

class Optimizer {
public:
	static Statement* optimize(Statement*, int, bool);
};

#endif /* include__optimization__optimizer_hpp */

