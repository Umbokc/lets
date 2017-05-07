#ifndef VARIABLES_H
#define VARIABLES_H

static std::map<std::string, Value*> variables = {
	{"PI", new NumberValue(M_PI)},
	{"E", new NumberValue(M_E)},
	{"GOLDEN_RATIO", new NumberValue(1.618)}
};

static std::stack<std::map<std::string, Value*>> thestack;

static NumberValue* ZERO = new NumberValue(0);

class Variables{
private:
public:

	static void push(){
		thestack.push(std::map<std::string, Value*>(variables));
	}

	static void pop(){
		variables = thestack.top();
	}

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
