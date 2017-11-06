//
//  visitors/function_adder.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef visitors__function_adder_h
#define visitors__function_adder_h

#include "abstract_visitor.h"

class FunctionAdder : virtual public AbstractVisitor{
public:
	void visit(FunctionDefineStatement *s){
		s->body->accept(s->body, this);
		s->execute();
	}
};

#endif /* visitors__function_adder_h */

