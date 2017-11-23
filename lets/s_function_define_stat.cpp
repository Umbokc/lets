//
//  s_function_define_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_function_define_stat.hpp"
#include "../include/l_user_define_function.hpp"
#include "../include/l_functions.hpp"

FunctionDefineStatement::FunctionDefineStatement(lets_str_t name, Arguments args, Statement *body):
name(std::move(name)), args(std::move(args)), body(std::move(body))
{}

void FunctionDefineStatement::execute(){
	if(this->name[0] == '_')
		Functions::set_constexpr(this->name, new UserDefineFunction(this->args, this->body));
	else
		Functions::set(this->name, new UserDefineFunction(this->args, this->body));
}

lets_str_t FunctionDefineStatement::beauty(){
	lets_str_t result = "def " + this->name;
	result +=  "(" + this->args.to_s() + " ):";
	result += this->body->to_s();
	result +=  "end";
	return result;
}

lets_str_t FunctionDefineStatement::to_s(){
	lets_str_t result = "def " + this->name;
	result +=  " ( " + this->args.to_s() + " ) ";
	result += this->body->to_s();
	return result;
}

FunctionDefineStatement::~FunctionDefineStatement(){
    // delete[] body;
}



