#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "function.h"
#include "function_container.h"

namespace LetsFunctions{
	std::map<std::string, FunctionContainer*> functions;
}

class Functions{
public:

	static bool is_exists(std::string key){
		return LetsFunctions::functions.find(key) != LetsFunctions::functions.end();
	}

	static bool is_constexpr(std::string key){
		return LetsFunctions::functions[key]->is_constant;
	}

	static Function* get(std::string key){
		if(!is_exists(key)) throw ParseException("Unknown function \"" + key + "\"");
		return LetsFunctions::functions[key]->body;
	}

	static void set(std::string key, Function* function){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot rewrite constant function \"" + key + "\"");
		LetsFunctions::functions[key] = new FunctionContainer(function);
	}
	
	static void set_constexpr(std::string key, Function* function){
		if(is_exists(key) && is_constexpr(key)) throw ParseException("Cannot rewrite constant function \"" + key + "\"");
		LetsFunctions::functions[key] =  new FunctionContainer(function, true);
	}

	static void set_lets_funcs(std::string key, Function* function, bool is_constexpr){
		LetsFunctions::functions[key] =  new FunctionContainer(function, is_constexpr);
	}

	~Functions();
};

#endif
