//
//  s_multi_assignment_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 15.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg
#include "../include/s_multi_assignment_stat.hpp"
#include "../include/l_array_value.hpp"
#include "../include/l_number_value.hpp"
#include "../include/e_value_expr.hpp"
#include "../include/tools.hpp"

MultiAssignmentStatement::MultiAssignmentStatement(lets_vector_t<Accessible*> targets, Expression *expression):
	targets(std::move(targets)), expression(std::move(expression)){}

void MultiAssignmentStatement::execute(){
	if(ArrayValue* arr = dynamic_cast<ArrayValue*>(expression->eval())){
		size_t size = targets.size();
		Value* val;
		for (int i = 0; i < size; ++i){
			targets.at(i)->set(arr->get_always(i));
		}
	}
}

lets_str_t MultiAssignmentStatement::to_s(){
    // return NS_Tools::string_format(
    //                                "[%s %s %s]",
    //                                targets->to_s().c_str(),
    //                                NS_Binary::OperatorString[operation].c_str(),
    //                                expression->to_s().c_str()
    //                                );
}

MultiAssignmentStatement::~MultiAssignmentStatement(){}
