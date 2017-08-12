#ifndef VALUE_H
#define VALUE_H
#include <iostream>
#include <string>

class Value {
public:

	virtual int as_int() = 0;
	virtual double as_number() = 0;
	virtual long long as_long() = 0;
	virtual std::string as_string() = 0;
	virtual std::string to_s() = 0;
	virtual Types type() = 0;

};

#endif