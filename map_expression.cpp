#ifndef MAP_EXPRESSION_H
#define MAP_EXPRESSION_H

#include <map>
#include <string>

class MapExpression : public Expression{
public:
	std::map<std::string, Expression*> elements; 

	MapExpression(std::map<std::string, Expression*> elements)
											:elements(std::move(elements)){}

	Value *eval(){
		MapValue* map_val = new MapValue();
		for (auto& elem: elements) {
			map_val->set(elem.first, elem.second->eval());
		}
		return map_val;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		std::string result = "{ ";

		int i = 0;
		int size = elements.size();
		for (auto& elem : elements){
			result += elem.first;	
			result +=  " : ";
			result += elem.second->to_s();
			if(i != size) result +=  ", ";
			i++;
		}
		result +=  " }";

		return result;
	}

	~MapExpression();
};

#endif
