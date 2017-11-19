//
//  s_multi_assignment_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 15.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream> // for dbg
#include "../include/s_multi_assignment_stat.hpp"
#include "../include/l_array_value.hpp"
#include "../include/l_map_value.hpp"
#include "../include/ex_execute.h"
#include "../include/tools.hpp"

MultiAssignmentStatement::MultiAssignmentStatement(lets_vector_t<Accessible*> targets, Expression *expression):
	targets(std::move(targets)), expression(std::move(expression)){}

void MultiAssignmentStatement::execute(){
	Value* val = expression->eval();
	if(ArrayValue* arr = dynamic_cast<ArrayValue*>(val)){
		size_t size = this->targets.size();
		for (int i = 0; i < size; ++i){
			this->targets.at(i)->set(arr->get_always(i));
		}
	} else if(MapValue* arr = dynamic_cast<MapValue*>(val)){
		size_t size = this->targets.size();
		for (int i = 0; i < size; ++i){
			this->targets.at(i)->set(arr->get_by_index(i));
		}
	} else {
		throw ExecuteException("Cannot assign non Array or Map value to multiple vars");
	}
}

lets_str_t MultiAssignmentStatement::to_s(){
	return NS_Tools::string_format(
		"[%s = %s]",
		(NS_Tools::vector_to_s<Accessible*>(targets, ", ")).c_str(),
		expression->to_s().c_str()
	);
}

MultiAssignmentStatement::~MultiAssignmentStatement(){}
