#ifndef ARRAYVALUE_H
#define ARRAYVALUE_H

class ArrayValue : public Value{
	std::vector<Value *> elements;
public:

	ArrayValue(int size){
		elements.resize(size);
	}

	ArrayValue(std::vector<Value *> elements){
		this->elements.swap(elements);
	}

	ArrayValue(ArrayValue *array){
		new ArrayValue(array->elements);
	}

	Value *get(int index){
		
		if(index < elements.size())
			return elements[index];
		
		throw std::runtime_error("Undefined index of array");
	}

	void set(int index, Value *value){
		elements[index] = value;
	}

	double asNumber(){
		throw std::runtime_error("Cannot cast array to number");
	} 
	
	std::string asString(){

		std::string result = "[ ";

		for(auto el : elements){
			result += el->to_s();
			result += ", ";
		}
		result += "\b\b ]";
		
		return result;
	} 
	
	std::string to_s(){
		return asString();
	}

	~ArrayValue();
	
};
#endif