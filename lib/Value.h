#ifndef VALUE
#define VALUE

class Value {
public:
	virtual double asDouble() = 0; 
	virtual std::string asString() = 0;
	virtual std::string to_s() = 0;
};

#endif