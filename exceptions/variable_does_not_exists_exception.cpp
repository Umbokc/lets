#ifndef VARIABLE_DOES_NOT_EXISTS_EXCEPTION_CPP
#define VARIABLE_DOES_NOT_EXISTS_EXCEPTION_CPP

class VariableDoesNotExistsException : public ParseException{
private:
	std::string variable;
public:
	
	VariableDoesNotExistsException(){}

	VariableDoesNotExistsException(std::string& variable)
													:variable(std::move(variable)){
		this->message = "Variable " + this->variable + " does not exists";
	}

	std::string get_variable(){ return this->variable; }

	~VariableDoesNotExistsException(){}

};

#endif