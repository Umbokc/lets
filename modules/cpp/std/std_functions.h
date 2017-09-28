#ifndef LETS_MODULE_STD_FUNCTIONS_H
#define LETS_MODULE_STD_FUNCTIONS_H
#include <limits>

namespace NSLM_Std_Funcs{

	class Echo : public Function{
	public:
		Echo(){}

		Value* execute(std::vector<Value *> args){
			for(auto a : args){
				std::cout.precision(a->to_s().length());
				std::cout << std::fixed << a->to_s() << std::endl;
			}
			return ZERO;
		}
		
		std::string to_s(){
			return "";
		}

		~Echo(){}
	};

	class Len : public Function{
	public:
		Value* execute(std::vector<Value *> args){
			if(args.size() != 1) throw ParseException("Function len(arg*) one args expected");
			return new NumberValue(args[0]->len());
		}
		
		std::string to_s(){ return ""; }
		
	};

	class NewArray : public Function{
	public:
		NewArray(){}
		Value* execute(std::vector<Value *> args){
			return create_array(args, 0);
		}
		std::string to_s(){
			return "";
		}
		~NewArray(){}
	private:
		ArrayValue* create_array(std::vector<Value *> args, int index){
			
			int size = (int)args[index]->as_number();
			int last = args.size() -1;
			
			ArrayValue *array = new ArrayValue(size);

			if(index == last){
				for (int i = 0; i < size; ++i){
					array->set(i, ZERO);
				}
			} else if(index < last) {
				for (int i = 0; i < size; ++i){
					array->set(i, create_array(args, index+1));
				}
			}

			return array;
		}
	};
}

#endif