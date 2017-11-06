//
//  optimization/variable_info.h
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef optimization__variable_info_h
#define optimization__variable_info_h

#include <string>
#include "../main.h"
#include "../l_value.h"

class VariableInfo {
public:
	Value* value;
	int modifications;

	lets_str_t to_s() {
		return (value == NULL ? "?" : value->to_s()) + " (" + to_str(modifications) + " mods)";
	}
};

#endif /* optimization__variable_info_h */

