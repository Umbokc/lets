//
//  include/lib/properties_container.hpp
//  lets
//
//  Created by Dragan Stepan on 21.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__lib__properties_container_hpp
#define include__lib__properties_container_hpp

#include <string>
#include <map>
#include "property.hpp"
#include "../main.h"

class PropertiesContainer {
public:

	lets_map_t<lets_str_t, Property> data;

	PropertiesContainer();

	bool is_exists(const lets_str_t&);
	bool is_constant(const lets_str_t&);

	Value* get(const lets_str_t&);

	void set(const lets_str_t&, Value*);
	void set(const lets_str_t&, Property);

	void remove(const lets_str_t&);

	size_t size();

	lets_str_t to_s();

	~PropertiesContainer();
};


#endif /* include__lib__properties_container_hpp */

