//
//  include/visitors/function_adder.h
//  lets
//
//  Created by Dragan Stepan on 05.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__visitors__function_adder_h
#define include__visitors__function_adder_h

#include "abstract_visitor.h"

class FunctionAdder : virtual public AbstractVisitor{
public:
	void visit(FunctionDefineStatement *s){
		s->body->accept(this);
		s->execute();
	}
};

#endif /* include__visitors__function_adder_h */

