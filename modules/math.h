#ifndef MATH_LETS_H
#define MATH_LETS_H

#include "../main.h"

class SIN_LETS : public Function{
public:
	SIN_LETS(){}
	Value* execute(std::vector<Value *> args){
		if(args.size() != 1) throw ParseException("One args expected");
		return new NumberValue(sin(args[0]->asNumber()));
	}
	~SIN_LETS();
};

class COS_LETS : public Function{
public:
	COS_LETS(){}
	Value* execute(std::vector<Value *> args){
		if(args.size() != 1) throw ParseException("One args expected");
		return new NumberValue(cos(args[0]->asNumber()));
	}
	~COS_LETS();
};

map<string, Function*> math_functions = {
	{"sin", new SIN_LETS()},
	{"cos", new COS_LETS()},
};

class Math_Functions{
public:

	static bool isExists(std::string key){
		return math_functions.find(key) != math_functions.end();
	}
	
	static Function* get(std::string key){
		if(!isExists(key)) throw ParseException("Unknown function \"" + key + "\"");
		return math_functions[key];
	}
	
	~Math_Functions();
};



#endif