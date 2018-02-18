//
//  include/tools.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__tools_hpp
#define include__tools_hpp

#include <sstream>
#include <string>
#include <vector>
#include "main.h"
#include "lib/number.hpp"

namespace NS_Tools{

	lets_str_t string_format(const lets_str_t fmt, ...);
	lets_str_t vector_s_to_s(const lets_vector_t<lets_str_t> elems, lets_str_t separator);

	template<typename T>
	lets_str_t convert_to_string(const T& val){
		std::ostringstream strs;
		strs << val;
		return strs.str();
	}

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

	Number* create_number(lets_str_t);

	inline bool fils_exists (const lets_str_t&);
	lets_str_t get_path( const lets_str_t&);
	lets_str_t splitpath( const lets_str_t&);
	lets_str_t get_curr_dir();

	// trim from start (in place)
	void ltrim(lets_str_t &s);
	// trim from end (in place)
	void rtrim(lets_str_t &);
	// trim from both ends (in place)
	void trim(lets_str_t &);
	// trim from start (copying)
	lets_str_t ltrim_copy(lets_str_t);
	// trim from end (copying)
	lets_str_t rtrim_copy(lets_str_t);
	// trim from both ends (copying)
	lets_str_t trim_copy(lets_str_t);

}


#endif /* include__tools_hpp */
