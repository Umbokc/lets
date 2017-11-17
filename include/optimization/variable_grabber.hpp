//
//  optimization/variable_grabber.hpp
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef optimization__variable_grabber_hpp
#define optimization__variable_grabber_hpp

#include <string>
#include <map>
#include "../main.h"

#include "variable_info.h"
#include "../visitors/optimization_visitor.h"

class VariablesGrabber: virtual public OptimizationVisitor<lets_map_t<lets_str_t, VariableInfo*>>{
private:
	bool grab_module_constants;
public:
	typedef lets_map_t<lets_str_t, VariableInfo*> THE_TYPE;

	static THE_TYPE getInfo(Node *);
	static THE_TYPE getInfo(Node*, bool);

	VariablesGrabber();
	VariablesGrabber(bool gmc);
	~VariablesGrabber();

	Node *visit(AssignmentExpression*, THE_TYPE);
	Node *visit(ForeachStatement*, THE_TYPE);
	// Node *visit(MatchExpression*, THE_TYPE);
	Node *visit(UnaryExpression*, THE_TYPE);
	// Node *visit(UseStatement*, THE_TYPE);

protected:
	bool visit_t(Arguments, Arguments, THE_TYPE);
private:
	VariableInfo *variable_info(THE_TYPE, lets_str_t);
};

#endif /* optimization__variable_grabber_hpp */

