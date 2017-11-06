//
//  ex_operation_is_not_supported.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef exceptions__operation_is_not_supported_h
#define exceptions__operation_is_not_supported_h

#include "ex_parse.h"

class OperationIsNotSupportedException : public ParseException{
public:
    OperationIsNotSupportedException(){}
    ~OperationIsNotSupportedException(){}
    
    OperationIsNotSupportedException(lets_str_t operation){
        this->message = "Operation " + operation + " is not supported";
    }
    
    OperationIsNotSupportedException(lets_str_t operation, lets_str_t message){
        this->message = "Operation " + operation + " is not supported " + message;
    }
    
};

#endif /* exceptions__operation_is_not_supported_h */
