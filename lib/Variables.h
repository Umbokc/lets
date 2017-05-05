#ifndef VARIABLES
#define VARIABLES

#define _USE_MATH_DEFINES
#include <cmath>
#include <map>

static std::map<std::string, Value*> variables = {
	{"PI", new NumberValue(M_PI)},
	{"E", new NumberValue(M_E)},
	{"GOLDEN_RATIO", new NumberValue(1.618)}
};

static Value* ZERO = new NumberValue(0);

class Variables{
public:

	static bool isExists(std::string key){
		return variables.find(key) != variables.end();
	}

	static Value* get(std::string key){
		if(!isExists(key)) return ZERO;
		return variables[key];
	}

	static void set(std::string key, Value* value){
		variables[key] = value;
	}

	~Variables();
};

Variables::~Variables(){
}

#endif
