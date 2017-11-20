//
//  s_include_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 20.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/s_include_stat.hpp"
#include "../include/ex_execute.h"
#include "../include/lets.hpp"
#include "../include/l_variables.h"

IncludeStatement::IncludeStatement(Expression *expression): expression(std::move(expression)){}

void IncludeStatement::execute(){
	try {
		lets_str_t file_name = expression->eval()->to_s();
		Statement* program = load_program(file_name);
		if (program != NULL) {
			lets_str_t parent_file = Variables::get("__file__")->to_s();
			Lets::current_file_name = realpath((Variables::get("__dir__")->to_s() + file_name).c_str(), NULL);
			Lets::init_vars_file(Lets::current_file_name);
			program->execute();
			Lets::current_file_name = parent_file;
			Lets::init_vars_file(Lets::current_file_name);
		}
	} catch (std::exception &ex) {
		throw ExecuteException(ex.what());
	}
}

Statement* IncludeStatement::load_program(lets_str_t path){
	return Lets::parse(Lets::tokenize(
		Lets::f2s( Variables::get("__dir__")->to_s() + path)
	));
}

lets_str_t IncludeStatement::to_s(){
	return "include " + expression->to_s();
}

IncludeStatement::~IncludeStatement(){}
