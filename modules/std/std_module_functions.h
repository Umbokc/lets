#ifndef LETS_MODULE_STD_FUNCTIONS_H
#define LETS_MODULE_STD_FUNCTIONS_H

namespace Lets_Modules_Std{

	class Echo : public Function{
	public:
		Echo(){}
		Value* execute(std::vector<Value *> args){
			for(auto a : args){
				std::cout << a->to_s() << std::endl;
			}
			return ZERO;
		}
		~Echo();
	};

	class NewArray : public Function{
	public:
		NewArray(){}
		Value* execute(std::vector<Value *> args){
			return create_array(args, 0);
		}
		~NewArray();
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