#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdarg>  // For va_start, etc.
#include <algorithm>

template <typename T> 
void dbg (const T& s){
	std::cout << "debug: " << s << std::endl;
}

template <typename T> 
void dbg (const T& s, bool end){
	dbg(s);
	std::cout << "exit" << std::endl;
	if(end){
		exit(0);
	}
}
namespace func {
	
	// template<typename Base, typename T>
	// inline bool instanceof(const T *ptr) {
	// 	return dynamic_cast<const Base*>(ptr) != nullptr;
	// }
	
	template<typename Base, typename T>
	inline bool instanceof(const T*) {
		return std::is_base_of<Base, T>::value;
	}
	template<typename T>
	std::string vector_to_s(const std::vector<T> elems, std::string separator) {
		std::string result = "";
		int size = elems.size();

		for(int i = 0; i < size; i++){
			result += elems[i]->to_s();
			if(i != size-1)
				result += separator;
		}

		return result;
	}

	template<typename T>
	std::string vector_to_s(const std::vector<T> elems) {
		return vector_to_s<T>(elems, ", ");
	}

	std::string string_format(const std::string fmt, ...) {
			int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
			std::string str;
			va_list ap;
			while (1) {     // Maximum two passes on a POSIX system...
					str.resize(size);
					va_start(ap, fmt);
					int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
					va_end(ap);
					if (n > -1 && n < size) {  // Everything worked
							str.resize(n);
							return str;
					}
					if (n > -1)  // Needed size returned
							size = n + 1;   // For null char
					else
							size *= 2;      // Guess at a larger size (OS specific)
			}
			return str;
	}

	std::string reverse_s(const std::string& the){
		std::string newstr("");
		for (int i = the.length() - 1; i >= 0; --i) {
			newstr += the[i];
		}
		return newstr;
	}

	template<class BidirIt>
	void reverse(BidirIt first, BidirIt last)
	{
		while ((first != last) && (first != --last)) {
			std::swap(*first++, *last);
		}
	}

	int find_c(std::string s, char c){
		for (int i = 0; i < s.length(); i++){
			if (s[i] == c){
				return i;
			}
		}
		return -1;
	}

	std::string f2s(std::string filename){
		std::string input;
		std::ifstream inf;

		inf.open ( filename );

		if (!inf){
			std::cout << "Cannot open file" << std::endl;
			exit(1);
		}

		getline ( inf, input, '\0' );
		inf.close();

		return input;
	}

	std::string appendctos(std::string const & s, char a) {
		return s + a;
	}

	std::string ctos(char a) {
		std::string s = "";
		return appendctos(s,a);
	}

	std::string dtos (double d) {
		std::ostringstream strs;
		strs << d;
		return strs.str();
	}

	// bool is_float( const std::string& my_string ) {
	//  bool Checked = true;
	//  bool was_dot = false;
	//  int i = 0;
	//  do {
	//    if (isdigit(my_string[i]) || my_string[i] == '.') {
	//      if (my_string[i] == '.') {
	//        if(was_dot){
	//          Checked = false;
	//          break;
	//        }
	//        was_dot = true;
	//        Checked = true;
	//      }

	//      i++;
	//    } else {
	//      //to the next character
	//      i++;
	//      Checked = false;
	//      break;
	//    }
	//  } while (my_string[i] != '\0');

	//  return Checked;
 //  }
}

#endif