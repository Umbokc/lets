#ifndef PARSE_EXCEPTION_CPP
#define PARSE_EXCEPTION_CPP

class ParseException {
protected:
	std::string message;
public:

	ParseException(){}
	
	ParseException(std::string message):message(std::move(message)){}
	std::string get_message(){ return message; }
	
	~ParseException(){}

};

#endif