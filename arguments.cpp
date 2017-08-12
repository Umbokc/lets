#ifndef ARGUMENTS_CPP
#define ARGUMENTS_CPP

#include <string>
#include <vector>

class Arguments {
private:
	int required;
	std::vector<Argument> arguments;
public:

	Arguments(){
		required = 0;
	}

	void add_required(std::string name){
		arguments.push_back(Argument(name));
		required++;
	}

	void add_optional(std::string name, Expression* expr){
		arguments.push_back(Argument(name, expr));
	}

	Argument get(int i){return arguments[i];}
	int get_required(){return required;}
	int get_size(){return arguments.size();}

	std::string to_s(){
		std::string result = "(";
		int size = arguments.size();
		for(int i = 0; i < size; i++){
			result += arguments[i].to_s();
			if(i != size-1)
				result += ", ";
		}
		
		result += ")";

		return result;
	}

	~Arguments(){}
};
#endif