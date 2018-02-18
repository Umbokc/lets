//
//  lets/expressions/map_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../../include/expressions/map_expr.hpp"

MapExpression::MapExpression(lets_map_t<Expression*, Expression*> elements)
	:elements(std::move(elements)){}

Value *MapExpression::eval(){
	MapValue* map_val = new MapValue();
	for (auto& elem: elements) {
		map_val->set(elem.first->eval(), elem.second->eval());
	}
	return map_val;
}

lets_str_t MapExpression::to_s(){
	lets_str_t result = "{";

	int i = 0;
	int size = (int)elements.size();
	for (auto& elem : elements){
		result += elem.first->to_s();
		result +=  " : ";
		result += elem.second->to_s();
		if(i != size) result +=  ", ";
		i++;
	}
	result +=  "}";

	return result;
}

MapExpression::~MapExpression(){}

