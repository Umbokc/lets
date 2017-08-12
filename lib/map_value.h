#ifndef MAP_VALUE_H
#define MAP_VALUE_H

#include <vector>
#include <string>

class MapValue : public Value{
	std::map<std::string, Value *> elems;
public:

	MapValue(){}
	
	MapValue(std::map<std::string, Value *> elems){
		this->elems.swap(elems);
	}

	MapValue(MapValue *map_val){
		new MapValue(map_val->elems);
	}

	// ArrayValue* to_pairs(){
		// int size = elems.size();
		// ArrayValue* result = new ArrayValue(size);
		// int i = 0;
		// std::vector<Value*> elem;
		// for(auto entry: elems){
		// 	elem = entry
		// 	result.set(i++, new ArrayValue());
		// }
	// }

	static MapValue *add(MapValue *arr, std::string key, Value *value){
		std::map<std::string, Value *> result = arr->get_all();
		result[key] = value;
		return new MapValue(result);
	}

	static MapValue *merge(MapValue *value1, MapValue *value2){
		std::map<std::string, Value *> arr1 = value1->get_all(),
															arr2 = value2->get_all();
		
		std::map<std::string, Value *> result;

		for(auto& elem : arr1){ result[elem.first] = elem.second; }
		for(auto& elem : arr2){ result[elem.first] = elem.second; }

		arr1.clear();
		arr2.clear();

		return new MapValue(result);
	}

	bool is_exists(std::string key){
		return elems.find(key) != elems.end();
	}

	Value *get(std::string key){
		if(is_exists(key))
			return elems[key];
		throw ParseException("Undefined key of map");
	}

	std::map<std::string, Value *> get_all(){
		return elems;
	}

	void set(std::string key, Value *value){
		elems[key] = value;
	}

	void set(std::string key, Function *function){
		elems[key] = new FunctionValue(function);
	}

	int as_int(){
		return as_number();
	}

	double as_number(){
		throw ParseException("Cannot cast map to number");
	} 

	long long as_long(){
		return as_number();
	} 
	
	std::string as_string(){
		std::string result = "{ ";

		int i = 0;
		int size = elems.size();
		for (auto& elem : elems){
			result += elem.first;
			result +=  " : ";
			result += elem.second->to_s();
			if(i != size-1) result +=  ", ";
			i++;
		}
		result +=  " }";

		return result;
	} 
	
	std::string to_s(){
		return as_string();
	}
	
	Types type(){
		return Types::T_MAP;
	}

	~MapValue();
	
};
#endif