//
//  l_functions.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/l_functions.hpp"
#include "../include/ex_error.h"
#include "../include/ex_execute.h"
#include "../include/tools.hpp"

lets_map_t<lets_str_t, FunctionContainer*> Functions::functions;

bool Functions::is_exists(lets_str_t key){
    return functions.find(key) != functions.end();
}

bool Functions::is_constexpr(lets_str_t key){
    return functions[key]->is_constant;
}

Function*Functions:: get(lets_str_t key){
    if(!is_exists(key)){
        throw ExecuteException(
                             NS_Tools::string_format(ExceptionsError::E_UNKNOWN_FUNC, key.c_str())
                             );
    }
    return functions[key]->body;
}

void Functions::set(lets_str_t key, Function* function){
    if(is_exists(key) && is_constexpr(key)){
        throw ExecuteException(
                             NS_Tools::string_format(ExceptionsError::E_CNN_REWRITE_FUNC, key.c_str())
                             );
    }
    functions[key] = new FunctionContainer(function);
}

void Functions::set_constexpr(lets_str_t key, Function* function){
    if(is_exists(key) && is_constexpr(key)){
        throw ExecuteException(
                             NS_Tools::string_format(ExceptionsError::E_CNN_REWRITE_FUNC, key.c_str())
                             );
    }
    functions[key] =  new FunctionContainer(function, true);
}

void Functions::set_lets_funcs(lets_str_t key, Function* function, bool is_constexpr){
    functions[key] =  new FunctionContainer(function, is_constexpr);
}

// Functions::static void show(){
// 	lets_str_t result = "Functions: \n";
// 		int i = 0;
// 		int size = functions.size();
// 		for (auto& elem : functions){
// 			result += "\t";
// 			result += elem.first;
// 			result +=  " : ";
// 			result += elem.second->body->to_s();

// 			if(i != size-1) result +=  ", \n";
// 			i++;
// 		}
// 		result +=  "\nend";

// 		std::cout << result << std::endl;
// }
