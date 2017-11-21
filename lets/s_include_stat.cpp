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
#include "../include/s_return_stat.hpp"
#include "../include/tools.hpp"

IncludeStatement::IncludeStatement(Expression *expression): expression(std::move(expression)){}

void IncludeStatement::execute(){
	eval();
}

Value* IncludeStatement::eval(){
	try {
		lets_str_t file_path = expression->eval()->to_s();

		if(file_path[0] != '/') file_path = Variables::get("__dir__")->to_s() + file_path;

		file_path = NS_Tools::get_path(file_path);

		Statement* program = load_program(file_path);
		if (program != NULL) {
			lets_str_t parent_file = Variables::get("__file__")->to_s();
			Lets::current_file_name = file_path;
			Lets::init_vars_file(Lets::current_file_name);
			program->execute();
			Lets::current_file_name = parent_file;
			Lets::init_vars_file(Lets::current_file_name);
		}
	} catch (ReturnStatement* &rs) {
		return rs->get_result();
	} catch (std::exception &ex) {
		throw ExecuteException(ex.what(), this->get_position_row(), this->get_position_col());
	}
	return NumberValue::ZERO;
}

Statement* IncludeStatement::load_program(const lets_str_t& path){
	return Lets::parse(Lets::tokenize(
		Lets::f2s(path)
	));
}

lets_str_t IncludeStatement::to_s(){
	return "include " + expression->to_s();
}

IncludeStatement::~IncludeStatement(){}
