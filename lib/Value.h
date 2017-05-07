#ifndef VALUE_H
#define VALUE_H

class Value {
public:
	virtual double asNumber() = 0; 
	virtual std::string asString() = 0;
	virtual std::string to_s() = 0;
};

#endif