//
//  lets/lib/user_define_function.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//
#include <iostream>
#include "../../include/lib/user_define_function.hpp"
#include "../../include/lib/null_value.hpp"
#include "../../include/lib/variables.hpp"
#include "../../include/statements/return_stat.hpp"
#include "../../include/exception/execute.h"
#include "../../include/tools.hpp"

UserDefineFunction::UserDefineFunction(Arguments args, Statement *body):
	args(std::move(args)), body(std::move(body)){}

int UserDefineFunction::get_args_count(){
	return args.get_size();
}

Value* UserDefineFunction::execute(FUNCS_ARGS values){
	int size = (int)values.size();
	int required = args.get_required();
	if(size < required) {
		throw ExecuteException(
			NS_Tools::string_format("Arguments count mismatch %d < %d", size, required)
		);
	}
	int total_size = get_args_count();
	if(size > total_size) {
		throw ExecuteException(
			NS_Tools::string_format("Arguments count mismatch %d > %d", size, required)
		);
	}

	Variables::push();
	try{
		for (int i = 0; i < size; ++i){
			Variables::set(get_arg_name(i), values[i]);
		}
		// optional args if exists
		for(int i = size; i < total_size; ++i){
			Argument arg = args.get(i);
			Variables::set(arg.get_name(), arg.get_value_expr()->eval());
		}
		body->execute();
		Variables::pop();
		return NullValue::THE_NULL;
	} catch(ReturnStatement *rs){
		Variables::pop();
		return rs->get_result();
	}
		// catch(SelfStatement *ss){
			// Value* res = execute(ss->args);
				// throw SelfStatementResponse(res);
			// return res;
	//}
	Variables::pop();
}

lets_str_t UserDefineFunction::get_arg_name(int i){
	if(i < 0 || i >= args.get_size()) return "";
	return args.get(i).get_name();
}

lets_str_t UserDefineFunction::to_s(){
	if(dynamic_cast<ReturnStatement*>(body)){
		return NS_Tools::string_format( "def %s = %s", args.to_s().c_str(),
			dynamic_cast<ReturnStatement*>(body)->expression->to_s().c_str());
	}
	return NS_Tools::string_format( "def %s %s", args.to_s().c_str(), body->to_s().c_str());
}
