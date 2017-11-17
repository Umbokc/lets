//
//  visitors/visitor_utils.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__visitor_utils_h
#define visitors__visitor_utils_h

#include <string>
#include <vector>
#include "../main.h"

#include "../node.h"

class VisitorUtils {
public:

	static bool is_value(Node* node);
	static bool is_variable(Node* node);

	// static Statement* include_program(IncludeStatement* s);
	// static bool is_integer_value(Node *node, int valueToCheck);
	// static bool is_valueasint(Node *node, int valueToCheck);
	// static bool is_constant_value(Node *node);
	// static bool is_same_variables(Node *n1, Node *n2);

	static lets_vector_t<lets_str_t> operators();
};

#endif /* visitors__visitor_utils_h */

