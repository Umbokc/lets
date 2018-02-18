//
//  include/lib/map_value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__map_value_hpp
#define include__lib__map_value_hpp

#include <string>
#include <map>
#include "../main.h"
#include "function.h"


class MapValue : public Value{
	lets_map_t<lets_str_t, Value *> elems;
public:

	MapValue();
	MapValue(lets_map_t<lets_str_t, Value *>&);
	MapValue(MapValue *);

	ArrayValue* to_pairs();

	bool is_exists(Value *);

	Value *get_by_index(size_t index);
	lets_map_t<lets_str_t, Value *> get_all();

	bool has(lets_str_t);
	bool has(lets_str_t, Value *);

	void set(Value *, Function *);

	LETS_REQUIRED_METHODS_VALUE_DECL()

	~MapValue();
};

namespace NS_MapValue{
	MapValue *add(MapValue*, Value*, Value*);
	MapValue *merge(MapValue*, MapValue*);
}

#endif /* include__lib__map_value_hpp */
