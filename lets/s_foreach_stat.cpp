//
//  s_foreach_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_foreach_stat.hpp"
#include "../include/s_break_stat.hpp"
#include "../include/s_continue_stat.hpp"
#include "../include/l_variables.h"
#include "../include/l_number_value.hpp"
#include "../include/l_string_value.hpp"
#include "../include/l_array_value.hpp"
#include "../include/l_map_value.hpp"

ForeachStatement::ForeachStatement(lets_str_t key, lets_str_t val, Expression *container, Statement *body) :
key(std::move(key)),
val(std::move(val)),
container(std::move(container)),
body(std::move(body))
{}

void ForeachStatement::execute(){
	Value* objs = container->eval();
	bool has_key = key != "";

	Value *prev_var_value__key = (has_key && Variables::is_exists(key)) ? Variables::get(key) : NULL;
	Value *prev_var_value__val = Variables::is_exists(val) ? Variables::get(val) : NULL;

	int i = 0;
	if(dynamic_cast<StringValue*>(objs)){
		lets_str_t str = dynamic_cast<StringValue*>(objs)->to_s();
		for(auto &entry : str){
			try{
				if(has_key){
					Variables::set(key, new NumberValue(i));
					i++;
				}
				
				Variables::set(val, new StringValue(entry));
				body->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
				// continue;
			}
		}
	}
	if(dynamic_cast<ArrayValue*>(objs)){
		lets_vector_t<Value *> arr = dynamic_cast<ArrayValue*>(objs)->get_all();
		for(Value *entry : arr){
			try{
				if(has_key){
					Variables::set(key, new NumberValue(i));
					i++;
				}
				Variables::set(val, entry);
				body->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
				// continue;
			}
		}
	}
	if(dynamic_cast<MapValue*>(objs)){
		lets_map_t<lets_str_t, Value *> map = dynamic_cast<MapValue*>(objs)->get_all();
		for(auto &entry : map){
			try{
				Variables::set(key, new StringValue(entry.first));
				Variables::set(val, entry.second);
				body->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
				// continue;
			}
		}
	}
	
	if(has_key && prev_var_value__key != NULL){
		Variables::set(key, prev_var_value__key);
	}
	if(prev_var_value__val != NULL){
		Variables::set(val, prev_var_value__val);
	}
}

lets_str_t ForeachStatement::to_s(){

	lets_str_t result = "for ";
	result += (key != "") ? key + ", " : ""; 
	result += val + " in " +
	container->to_s() + " :\n" + 
	body->to_s() + "end";

	return result;
}

ForeachStatement::~ForeachStatement(){
}

