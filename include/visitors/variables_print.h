//
//  include/visitors/variables_print.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__visitors__variables_print_h
#define include__visitors__variables_print_h

#include "abstract_visitor.h"

class VariablesPrint : virtual public AbstractVisitor{
public:

	void visit(VariableExpression *s){
		lets_output(s->name);
	}

};

#endif /* include__visitors__variables_print_h */

