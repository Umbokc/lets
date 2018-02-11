//
//  include/exception/operation_is_not_supported.h
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__exception__operation_is_not_supported_h
#define include__exception__operation_is_not_supported_h

#include "execute.h"

class OperationIsNotSupportedException : public ExecuteException{
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

#endif /* include__exception__operation_is_not_supported_h */
