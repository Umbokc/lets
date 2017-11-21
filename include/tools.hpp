//
//  tools.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef tools_hpp
#define tools_hpp

#include <string>
#include <vector>
#include "main.h"

namespace NS_Tools{
	lets_str_t string_format(const lets_str_t fmt, ...);
	
	lets_str_t vector_s_to_s(const lets_vector_t<lets_str_t> elems, lets_str_t separator);
	
	template<typename T> lets_str_t vector_to_s(const lets_vector_t<T> elems, lets_str_t separator) {
		lets_str_t result = "";
		int size = (int)elems.size();

		for (int i = 0; i < size; i++) {
			result += elems[i]->to_s();
			if (i != size - 1)
				result += separator;
		}

		return result;
	}

	inline bool fils_exists (const lets_str_t&);
	lets_str_t get_path( const lets_str_t&);

	lets_str_t splitpath( const lets_str_t&);

	lets_str_t get_curr_dir();
}


#endif /* tools_hpp */
