//
//  include/optimization/variable_info.h
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__optimization__variable_info_h
#define include__optimization__variable_info_h

#include <string>
#include "../main.h"
#include "../lib/value.h"

class VariableInfo {
public:
	Value* value;
	int modifications;

	lets_str_t to_s() {
		return (value == NULL ? "?" : value->to_s()) + " (" + to_str(modifications) + " mods)";
	}
};

#endif /* include__optimization__variable_info_h */

