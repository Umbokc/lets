#ifndef ARRAY_VALUE_H
#define ARRAY_VALUE_H

#include <vector>
#include <string>

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

	static ArrayValue *add(ArrayValue *arr, Value *value){
		std::vector<Value *> result = arr->get_all();
		result.push_back(value);
		return new ArrayValue(result);
	}

	static ArrayValue *add_forward(ArrayValue *arr, Value *value){
		std::vector<Value *> result = arr->get_all();
		result.insert(result.begin(), value);
		return new ArrayValue(result);
	}

	static ArrayValue *merge(ArrayValue *value1, ArrayValue *value2){
		std::vector<Value *> arr1 = value1->get_all(),
		arr2 = value2->get_all();

		std::vector<Value *> result;

		result.reserve(arr1.size() + arr2.size());
		result.insert(result.end(), arr1.begin(), arr1.end());
		result.insert(result.end(), arr2.begin(), arr2.end());
		
		arr1.clear();
		arr2.clear();

		return new ArrayValue(result);
	}

	Value *get(int index){
		
		if(index < elements.size())
			return elements[index];
		
		throw ParseException("Undefined index of array");
	}

	std::vector<Value *> get_all(){
		return elements;
	}

	void set(int index, Value *value){
		elements[index] = value;
	}


	int as_int(){
		return as_number();
	}

	double as_number(){
		throw ParseException("Cannot cast array to number");
	} 
	
	std::string as_string(){

		std::string result = "[ ";

		for(auto el : elements){
			result += el->to_s();
			result += ", ";
		}
		if(elements.size() > 1)
			result += "\b\b";
		result += " ]";
		
		return result;
	} 
	
	std::string to_s(){
		return as_string();
	}
	
	Types type(){
		return Types::T_ARRAY;
	}

	~ArrayValue();
	
};
#endif