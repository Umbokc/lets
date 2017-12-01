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

#include "../include/visitors/function_adder.h"

IncludeStatement::IncludeStatement(Expression *expression): expression(std::move(expression)){}

void IncludeStatement::execute(){
	eval();
}

Value* IncludeStatement::eval(){

	lets_str_t file_path = expression->eval()->to_s();
	if(file_path[0] != '/') file_path = Variables::get("__dir__")->to_s() + file_path;
	Statement* program;

	try {
		file_path = NS_Tools::get_path(file_path);
	} catch (std::exception &ex) {
		throw ExecuteException(ex.what(), this->get_position_row(), this->get_position_col());
	}

	try{
		program = load_program(file_path);
	} catch (LexerException &le) {
		show_lets_error(le.head, file_path, to_str(le.row), to_str(le.col), le.get_message())
	} catch (ParseException &pe) {
		show_lets_error(pe.head, file_path, to_str(pe.row), to_str(pe.col), pe.get_message())
	}

	if (program != NULL) {

		lets_str_t parent_file = Variables::get("__file__")->to_s();
		Lets::current_file_name = file_path;
		Lets::init_vars_file(Lets::current_file_name);

		if(Lets::ModeFunctionAdder) { program->accept(new FunctionAdder()); Lets::ModeFunctionAdder = false;}

		try{
			program->execute();
		} catch (ReturnStatement* &rs) {
			Lets::current_file_name = parent_file;
			Lets::init_vars_file(Lets::current_file_name);
			return rs->get_result();
		} catch (ExecuteException &ee) {
			Lets::current_file_name = parent_file;
			Lets::init_vars_file(Lets::current_file_name);
			throw ExecuteException(ee.get_message(), ee.row, ee.col, file_path);
		}

		Lets::current_file_name = parent_file;
		Lets::init_vars_file(Lets::current_file_name);
	}

	return NumberValue::ZERO;
}

Statement* IncludeStatement::load_program(const lets_str_t& path){
	return Lets::parse(Lets::tokenize(
		Lets::f2s(path), false
	), false);
}

lets_str_t IncludeStatement::to_s(){
	return "include " + expression->to_s();
}

IncludeStatement::~IncludeStatement(){}
