#ifndef FUNCTIONDEFINE_H
#define FUNCTIONDEFINE_H

class FunctionDefine : public Statement{
private:
	std::string name;
	std::vector<std::string> argNames;
	Statement *body;
public:
	
	FunctionDefine(std::string name, std::vector<std::string> argNames, Statement *body){
		this->name = name;
		this->argNames = argNames;
		this->body = body;
	}

	void execute(){
		Functions::set(name, new UserDefineFunction(argNames, body));
	}
	
	std::string to_s(){
		std::string result = "def " + name + " ( ";
		
		for (std::string argument : argNames){
			result += argument;
			result +=  ", ";
		}

		result += "\b\b ) ";
		
		result += body->to_s();

		return result;
	}

	~FunctionDefine();
};
#endif
