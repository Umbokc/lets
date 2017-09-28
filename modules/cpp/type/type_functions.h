#ifndef LETS_MODULE_TYPE_FUNCTIONS_H
#define LETS_MODULE_TYPE_FUNCTIONS_H
#include <limits>

namespace NSLM_Type_Funcs{

	class to_int : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function int(arg*) one args expected");
			return new NumberValue(args[0]->as_int());
		}
		
		std::string to_s(){ return ""; }
		
	};

	class to_string : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function string(arg*) one args expected");
			return new StringValue(args[0]->to_s());
		}
		
		std::string to_s(){ return ""; }
		
	};

}

#endif