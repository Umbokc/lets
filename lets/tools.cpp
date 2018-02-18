//
//  tools.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <algorithm> 
#include <cctype>
#include <locale>
#include "../include/tools.hpp"

namespace NS_Tools {

	lets_str_t string_format(const lets_str_t fmt, ...) {
		int size = ((int)fmt.size()) * 2 + 50;    // Use a rubric appropriate for your code
		lets_str_t str;
		va_list ap;
		while (1) {   // Maximum two passes on a POSIX system...
			str.resize(size);
			va_start(ap, fmt);
			int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
			va_end(ap);
			if (n > -1 && n < size) {   // Everything worked
				str.resize(n);
				return str;
			}
			if (n > -1)   // Needed size returned
				size = n + 1;   // For null char
			else
				size *= 2;    // Guess at a larger size (OS specific)
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


	Number* create_number(lets_str_t text){

		Number* value;

		if(text.find('.') != lets_str_t::npos){
			value = new Number(atof(&text[0u]));
		}else{
			try{
				value = new Number(std::stoi(text));
			} catch (std::exception& e){
				try{
					text = text.substr(0, 19);
					value = new Number(std::atol(&text[0u]));
				} catch (std::exception& e){
					throw std::runtime_error("Very big number: " + text);
				}
			}
		}

		return value;
	}

	inline bool fils_exists (const lets_str_t& name) {
		struct stat buffer;   
		return (stat (name.c_str(), &buffer) == 0); 
	}

	lets_str_t get_path( const lets_str_t& str){
		if(fils_exists(str))
			return realpath(str.c_str(), NULL);
		else
			throw std::runtime_error("File '"+ str +"' not found");
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

	void ltrim(lets_str_t &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	void rtrim(lets_str_t &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	void trim(lets_str_t &s) {
		ltrim(s);
		rtrim(s);
	}

	lets_str_t ltrim_copy(lets_str_t s) {
		ltrim(s);
		return s;
	}

	lets_str_t rtrim_copy(lets_str_t s) {
		rtrim(s);
		return s;
	}

	lets_str_t trim_copy(lets_str_t s) {
		trim(s);
		return s;
	}
}
