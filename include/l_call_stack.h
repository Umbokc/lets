//
//  l_call_stack.h
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef l_call_stack_h
#define l_call_stack_h

#include <vector>
#include <string>
#include <deque>
#include "main.h"

#include "l_function.h"
#include "tools.hpp"

class CallInfo {
private:
    lets_str_t name;
    Function* function;
public:
    
    CallInfo(){}
    
    CallInfo(lets_str_t name, Function* function):
        name(std::move(name)), function(std::move(function)){}
    
    lets_str_t to_s(){
        return NS_Tools::string_format("%s: %s", name.c_str(), function->to_s().c_str());
    }
    
    ~CallInfo(){}
};

struct CallStack {

    static std::deque<CallInfo*> calls;
    
    static void clear();
    
    static void enter(lets_str_t name, Function* function);
    
    static void exit();
};

std::deque<CallInfo*> CallStack::calls;

void CallStack::clear(){
    calls.clear();
}

void CallStack::enter(lets_str_t name, Function* function){
    calls.push_back(new CallInfo(name, function));
}

void CallStack::exit(){
    calls.pop_back();
}

#endif /* l_call_stack_h */
