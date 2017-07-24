#ifndef PARSE_EXCEPTION_CPP
#define PARSE_EXCEPTION_CPP

class ParseException {
public:
	std::string message;
	ParseException(std::string message){
		this->message = message;
	}
};

#endif