//
//  arguments.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/arguments.hpp"

Arguments::Arguments(){
	required = 0;
}

void Arguments::add_required(lets_str_t name){
	arguments.push_back(Argument(name));
	required++;
}

void Arguments::add_optional(lets_str_t name, Expression* expr){
	arguments.push_back(Argument(name, expr));
}

Argument Arguments::get(int i){
	return arguments[i];
}

int Arguments::get_required(){
	return required;
}

int Arguments::get_size(){
	return (int)arguments.size();
}

lets_str_t Arguments::to_s(){
	lets_str_t result = "";
	int size = (int)arguments.size();
	for(int i = 0; i < size; i++){
		result += arguments[i].to_s();
		if(i != size-1)
			result += ", ";
	}
	result += "";

	return result;
}

Arguments::~Arguments(){}
