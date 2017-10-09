#ifndef OPERATION_IS_NOT_SUPPORTED_EXCEPTION_CPP
#define OPERATION_IS_NOT_SUPPORTED_EXCEPTION_CPP

class OperationIsNotSupportedException : public ParseException{
public:
	OperationIsNotSupportedException(){}
	~OperationIsNotSupportedException(){}
	
	OperationIsNotSupportedException(std::string operation){
		this->message = "Operation " + operation + " is not supported";
	}

	OperationIsNotSupportedException(std::string operation, std::string message){
		this->message = "Operation " + operation + " is not supported " + message;
	}

};

#endif