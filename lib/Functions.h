#ifndef FUNCTIONS_H
#define FUNCTIONS_H

static Value* F_ZERO = new NumberValue(0);

class Sin : public Function{
public:
	Sin(){}
	Value* execute(std::vector<Value *> args){
		if(args.size() != 1) throw std::runtime_error("One args expected");
		return new NumberValue(sin(args[0]->asNumber()));
	}
	~Sin();
};

class Cos : public Function{
public:
	Cos(){}
	Value* execute(std::vector<Value *> args){
		if(args.size() != 1) throw std::runtime_error("One args expected");
		return new NumberValue(cos(args[0]->asNumber()));
	}
	~Cos();
};

class Echo : public Function{
public:
	Echo(){}
	Value* execute(std::vector<Value *> args){
		for(auto a : args){
			std::cout << a->to_s() << std::endl;
		}
		return F_ZERO;
	}
	~Echo();
};

class NewArray : public Function{
public:
	NewArray(){}
	Value* execute(std::vector<Value *> args){
		return createArray(args, 0);
	}
	~NewArray();
private:
	ArrayValue* createArray(std::vector<Value *> args, int index){
		
		int size = (int) args[index]->asNumber();
		int last = args.size() -1;
		
		ArrayValue *array = new ArrayValue(size);

		if(index == last){
			for (int i = 0; i < size; ++i){
				array->set(i, F_ZERO);
			}
		} else if(index < last) {
			for (int i = 0; i < size; ++i){
				array->set(i, createArray(args, index+1));
			}
		}

		return array;
	}
};


std::map<std::string, Function*> thefunctions = {
	{"sin", new Sin()},
	{"cos", new Cos()},
	{"echo", new Echo()},
	{"newArray", new NewArray()},
};

bool Functions::isExists(std::string key){
	return thefunctions.find(key) != thefunctions.end();
}

Function* Functions::get(std::string key){
	if(!isExists(key)) throw std::runtime_error("Unknown function " + key);
	return thefunctions[key];
}

void Functions::set(std::string key, Function* function){
	thefunctions[key] = function;
}

#endif
