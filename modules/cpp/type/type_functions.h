#ifndef LETS_MODULE_FUNCTIONS_TYPE_H
#define LETS_MODULE_FUNCTIONS_TYPE_H
#include <limits>
#include <string>

namespace NS_LM_F_Type{

	class NS_LM_Fs_to_int : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function int(arg*) one args expected");
			return new NumberValue(args[0]->as_int());
		}
		
		std::string to_s(){ return ""; }
		
	};

	class NS_LM_Fs_to_string : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function string(arg*) one args expected");
			return new StringValue(args[0]->to_s());
		}
		
		std::string to_s(){ return ""; }
		
	};

	class NS_LM_Fs_call_func : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			int args_size = args.size();
			if(args_size < 1 && args_size > 3){
				throw ParseException(
					"Function call_f(string name_f*, array args_function=false, string format_function_show = '%s( %s ) = ') takes three or one argument"
				);
			}
			FunctionalExpression* the_function = new FunctionalExpression(new ValueExpression(args[0]->to_s()));
			
			if(args_size >= 2){
				std::vector<Value *> arguments_f;
				if(dynamic_cast<ArrayValue*>(args[1])){
					arguments_f = dynamic_cast<ArrayValue*>(args[1])->get_all();
				} else {
					throw ParseException("Function call_f(..., array args_function=false, ...), the second argument expected array");
				}
				int size = arguments_f.size();
				for(int i = 0; i < size; i++){
					the_function->add_arguments(new ValueExpression(arguments_f[i]));
				}
			}

			if(args_size == 3){
				std::string format_function_show = "%s(%s) = ";
				// format_function_show = args[2]->to_s();
				std::cout << func::string_format(
					format_function_show,
					args[0]->to_s().c_str(),
					the_function->args_to_s().c_str()
				);
			}

			return the_function->eval();
		}
		
		std::string to_s(){ return ""; }
		
	};

}

#endif