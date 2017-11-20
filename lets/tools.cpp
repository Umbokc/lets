//
//  tools.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <sstream>
#include <errno.h>
#include <unistd.h>
#include "../include/tools.hpp"

namespace NS_Tools {

	lets_str_t string_format(const lets_str_t fmt, ...) {
		int size = ((int)fmt.size()) * 2 + 50;		// Use a rubric appropriate for your code
		lets_str_t str;
		va_list ap;
		while (1) {		// Maximum two passes on a POSIX system...
			str.resize(size);
			va_start(ap, fmt);
			int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
			va_end(ap);
			if (n > -1 && n < size) {		// Everything worked
				str.resize(n);
				return str;
			}
			if (n > -1)		// Needed size returned
				size = n + 1;		// For null char
			else
				size *= 2;		// Guess at a larger size (OS specific)
		}
		return str;
	}

	lets_str_t vector_s_to_s(const lets_vector_t<lets_str_t> elems, lets_str_t separator) {
		lets_str_t result = "";
		int size = (int)elems.size();

		for (int i = 0; i < size; i++) {
			result += elems[i];
			if (i != size - 1)
				result += separator;
		}

		return result;
	}

	lets_str_t splitpath( const lets_str_t& str){

		lets_vector_t<lets_str_t> result;

		char const* pch = str.c_str();
		char const* start = pch;
		for(; *pch; ++pch){
			if (*pch == '/'){
				if (start != pch){
					lets_str_t str(start, pch);
					result.push_back(str);
				} else{
					result.push_back("");
				}
				start = pch + 1;
			}
		}

		lets_str_t r("");
		for(auto &i : result){
			r += i;
			r += "/";
		}

		return r;

	}

	lets_str_t get_curr_dir(){
    char temp [ PATH_MAX ];

    if ( getcwd(temp, PATH_MAX) != 0) 
        return lets_str_t ( temp );

    int error = errno;

    switch ( error ) {
        // EINVAL can't happen - size argument > 0

        // PATH_MAX includes the terminating nul, 
        // so ERANGE should not be returned

        case EACCES:
            throw std::runtime_error("Access denied");

        case ENOMEM:
            // I'm not sure whether this can happen or not 
            throw std::runtime_error("Insufficient storage");

        default: {
            std::ostringstream str;
            str << "Unrecognised error" << error;
            throw std::runtime_error(str.str());
        }
    }
	}
}
