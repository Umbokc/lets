//
//  include/lib/number.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__number_hpp
#define include__lib__number_hpp

#include "../main.h"
#include <sstream>

namespace NS_Number {
	typedef union {
		int i;
		double d;
		long l;
	} evil;

	typedef enum {
		TYPE_INT,
		TYPE_DOUBLE,
		TYPE_LONG
	} types;
}

class Number {
	NS_Number::evil val;
	NS_Number::types type;
public:

	Number();

	Number(int&);
	Number(double&);
	Number(long&);

	Number& operator=(const Number&);
	void operator=(int);
	void operator=(double);
	void operator=(long);

	int as_int();
	double as_double();
	long as_long();

	bool is_int();
	bool is_double();
	bool is_long();

	lets_str_t as_string();
	lets_str_t to_s();

	template<class T> void add(T);
	template<typename T> T as_number();

	~Number();
};

#endif /* include__lib__number_hpp */
