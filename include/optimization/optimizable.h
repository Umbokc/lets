//
//  optimization/optimizable.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef optimization__optimizable_h
#define optimization__optimizable_h

#include <string>
#include "../main.h"
#include "../node.h"

class Optimizable {
public:
	virtual Node *optimize(Node*) = 0;
	virtual int optimizations_count() = 0;
	virtual lets_str_t summary_info() = 0;
	// virtual ~Optimizable(){}
};

#endif /* optimization__optimizable_h */

