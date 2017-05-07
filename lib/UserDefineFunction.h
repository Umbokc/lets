#ifndef USERDEFINEFUNCTION_H
#define USERDEFINEFUNCTION_H

class UserDefineFunction : public Function {
	std::vector<std::string> argNames;
	Statement *body;
public:

	UserDefineFunction(std::vector<std::string> argNames, Statement *body){
		this->argNames = argNames;
		this->body = body;
	}

	int getArgsCount(){
		return argNames.size();
	}

	std::string getArgName(int index){
		if(index < 0 || index >= getArgsCount()) return "";
		return argNames[index];
	}

	Value* execute(std::vector<Value *> args){
		try{
			body->execute();
			return new NumberValue(0); 
		} catch(ReturnStatement *rs){
			return rs->getResult();
		}

	}

};

#endif