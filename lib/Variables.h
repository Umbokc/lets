#ifndef VARIABLES_H
#define VARIABLES_H

using namespace std;

static map<string, Value*> variables = {
	{"PI", new NumberValue(M_PI)},
	{"E", new NumberValue(M_E)},
	{"GOLDEN_RATIO", new NumberValue(1.618)}
};

static stack<map<string, Value*>> thestack;

static NumberValue* ZERO = new NumberValue(0);

class Variables{
private:
public:

	static void push(){
		thestack.push(map<string, Value*>(variables));
	}

	static void pop(){
		thepop(&variables, thestack, thestack.size());
	}

	static bool isExists(string key){
		return variables.find(key) != variables.end();
	}

	static Value* get(string key){
		if(!isExists(key)) return ZERO;
		return variables[key];
	}

	static void set(string key, Value* value){
		variables[key] = value;
	}

private:
	static void thepop(map<string, Value*> *var, stack<map<string, Value*>> the_stack, int size){

		int i = 0;
		map<string, Value*> temp[size];
		while (!thestack.empty()){
			temp[i] = thestack.top();
			thestack.pop();
			++i;
		}

		for (int j = size - 1, l = 0; j >= 0; --j, ++l) {
			var[l] = temp[j];
		}

	}

	~Variables();
};

Variables::~Variables(){
}

#endif
