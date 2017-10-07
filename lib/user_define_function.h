#ifndef USER_DEFINE_FUNCTION_H
#define USER_DEFINE_FUNCTION_H
#include <vector>
#include <string>

class UserDefineFunction : public Function {
	Arguments args;
	Statement *body;
public:

	UserDefineFunction(Arguments args, Statement *body):
				args(std::move(args)), body(std::move(body)){}

	int get_args_count(){
		return args.get_size();
	}

	Value* execute(std::vector<Value *> values){
		int size = values.size();
		int required = args.get_required();
		if(size < required) {
			throw ParseException(
				func::string_format(
					"Arguments count mismatch %d < %d", 
					size, required
				)
			);
		}
		int total_size = get_args_count();
		if(size > total_size) {
			throw ParseException(
				func::string_format(
					"Arguments count mismatch %d > %d", 
					size, required
				)
			);
		}
		Variables::push();
		try{
			for (int i = 0; i < size; ++i){
				Variables::set(get_arg_name(i), values[i]);
			}
			// optional args if exists
			for(int i = size; i < total_size; ++i){
				Argument arg = args.get(i);
				Variables::set(arg.get_name(), arg.get_value_expr()->eval());
			}

			body->execute();
			Variables::pop();
			return ZERO;
		} catch(ReturnStatement *rs){
			Variables::pop();
			return rs->get_result();
		} catch(SelfStatement *ss){
			Value* res = execute(ss->args);
			throw new SelfStatementResponse(res);
			return res;
		}
	}

	std::string get_arg_name(int i){
		if(i < 0 || i >= args.get_size()) return "";
		return args.get(i).get_name();
	}

	std::string to_s(){
		// if(func::instanceof<ReturnStatement>(body)){
			return func::string_format(
				"def %s = %s", 
				args.to_s().c_str(),
				body->to_s().c_str()
			);
		// }
	}
};

#endif