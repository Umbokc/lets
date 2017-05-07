#ifndef ARRAYVALUE_H
#define ARRAYVALUE_H

class ArrayValue : public Value{
	std::vector<Value *> elements;
public:

	ArrayValue(){
	}

	ArrayValue(std::vector<Value *> elements){
		this->elements.swap(elements);
	}

	ArrayValue(ArrayValue *array){
		ArrayValue(array->elements);
	}

	Value *get(int index){
		return elements[index];
	}

	void set(int index, Value *value){
		elements[index] = value;
	}

	double asNumber(){
		throw std::runtime_error("Cannot cast array to number");
	} 
	
	std::string asString(){

		std::string result = "";

		for(auto el : elements){
			result += el->to_s();
		}

		result.push_back('\n');
		
		return result;
	} 
	
	std::string to_s(){
		return asString();
	}

	~ArrayValue();
	
};
#endif