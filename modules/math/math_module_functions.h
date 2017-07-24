#ifndef LETS_MODULE_MATH_FUNCTIONS_H
#define LETS_MODULE_MATH_FUNCTIONS_H

namespace Lets_Modules_Math{
	
	class Sin : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(sin(args[0]->as_number()));
		}
	};
	
	class Cos : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(cos(args[0]->as_number()));
		}
	};
	
	class Tan : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(tan(args[0]->as_number()));
		}
	};
	
	class Acos : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(acos(args[0]->as_number()));
		}
	};
	
	class Asin : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(asin(args[0]->as_number()));
		}
	};
	
	class Atan : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(atan(args[0]->as_number()));
		}
	};

	class Atan2 : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 2) throw ParseException("Two args expected");
			return new NumberValue(atan2(args[0]->as_number(), args[1]->as_number()));
		}
	};
	
	class Cosh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(cosh(args[0]->as_number()));
		}
	};
	
	class Sinh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(sinh(args[0]->as_number()));
		}
	};
	
	class Tanh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(tanh(args[0]->as_number()));
		}
	};
	
	class Acosh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(acosh(args[0]->as_number()));
		}
	};
	
	class Asinh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(asinh(args[0]->as_number()));
		}
	};

	class Atanh : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("One args expected");
			return new NumberValue(atanh(args[0]->as_number()));
		}
	};

}

#endif