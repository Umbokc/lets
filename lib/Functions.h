#ifndef FUNCTIONS_H
#define FUNCTIONS_H

static Value* F_ZERO = new NumberValue(0);

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
	{"echo", new Echo()},
	{"newArray", new NewArray()},
};

bool Functions::isExists(std::string key){
	return thefunctions.find(key) != thefunctions.end();
}

Function* Functions::get(std::string key){
	if(!Functions::isExists(key)) throw ParseException("Unknown function \"" + key + "\"");
	return thefunctions[key];
}

void Functions::set(std::string key, Function* function){
	thefunctions[key] = function;
}

#endif
