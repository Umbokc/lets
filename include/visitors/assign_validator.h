//
//  visitors/assign_validator.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__assign_validator_h
#define visitors__assign_validator_h

#include "abstract_visitor.h"
#include "../ex_parse.h"
#include "../l_variables.h"

class AssignValidator : virtual public AbstractVisitor{
public:

	void visit(AssignmentStatement *s){
		s->expression->accept(s->expression, this);
		if(Variables::is_exists(s->variable)){
			throw ParseException("Cannon assign value to constant");
		}
	}

};

#endif /* visitors__assign_validator_h */

