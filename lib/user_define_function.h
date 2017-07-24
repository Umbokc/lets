#ifndef USER_DEFINE_FUNCTION_H
#define USER_DEFINE_FUNCTION_H
#include <vector>
#include <string>

class UserDefineFunction : public Function {
	std::vector<std::string> arg_names;
	Statement *body;
public:

	UserDefineFunction(std::vector<std::string> arg_names, Statement *body){
		this->arg_names = arg_names;
		this->body = body;
	}

	int get_args_count(){
		return arg_names.size();
	}

	std::string get_arg_name(int index){
		if(index < 0 || index >= get_args_count()) return "";
		return arg_names[index];
	}

	Value* execute(std::vector<Value *> args){
		try{
			body->execute();
			return ZERO; 
		} catch(ReturnStatement *rs){
			return rs->get_result();
		}

	}

};

#endif