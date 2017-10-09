#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "function.h"
#include "function_container.h"

namespace Functions{
	std::map<std::string, FunctionContainer*> functions;

	static bool is_exists(std::string key){
		return functions.find(key) != functions.end();
	}

	static bool is_constexpr(std::string key){
		return functions[key]->is_constant;
	}

	static Function* get(std::string key){
		if(!is_exists(key)) throw ParseException("Unknown function \"" + key + "\"");
		return functions[key]->body;
	}

	static void set(std::string key, Function* function){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot rewrite constant function \"" + key + "\"");
		functions[key] = new FunctionContainer(function);
	}
	
	static void set_constexpr(std::string key, Function* function){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot rewrite constant function \"" + key + "\"");
		functions[key] =  new FunctionContainer(function, true);
	}

	static void set_lets_funcs(std::string key, Function* function, bool is_constexpr){
		functions[key] =  new FunctionContainer(function, is_constexpr);
	}

	// static void show(){
	// 	std::string result = "Functions: \n";
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

};

#endif
