#ifndef LETS_MODULE_MATH_FUNCTIONS_H
#define LETS_MODULE_MATH_FUNCTIONS_H

namespace Lets_Modules_Math{
	
	class LMM_Sin : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function sin(arg*) one args expected");
			return new NumberValue(sin(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Cos : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function cos(arg*) one args expected");
			return new NumberValue(cos(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Tan : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function tan(arg*) one args expected");
			return new NumberValue(tan(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Acos : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function acos(arg*) one args expected");
			return new NumberValue(acos(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Asin : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function asin(arg*) one args expected");
			return new NumberValue(asin(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Atan : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function atan(arg*) one args expected");
			return new NumberValue(atan(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};

	class LMM_Atan2 : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 2) throw ParseException("Function atan2(arg*, arg*) two args expected");
			return new NumberValue(atan2(args[0]->as_number(), args[1]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Cosh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function cosh(arg*) one args expected");
			return new NumberValue(cosh(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Sinh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function sinh(arg*) one args expected");
			return new NumberValue(sinh(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Tanh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function tanh(arg*) one args expected");
			return new NumberValue(tanh(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Acosh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function acosh(arg*) one args expected");
			return new NumberValue(acosh(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};
	
	class LMM_Asinh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function asinh(arg*) one args expected");
			return new NumberValue(asinh(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};

	class LMM_Atanh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function atanh(arg*) one args expected");
			return new NumberValue(atanh(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};

	class LMM_Sqrt : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function sqrt(arg*) one args expected");
			return new NumberValue(sqrt(args[0]->as_number()));
		}
		
		std::string to_s(){ return ""; }
		
	};

}

#endif