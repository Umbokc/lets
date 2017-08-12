#ifndef CALL_STACK_H
#define CALL_STACK_H

#include <deque>
#include "function.h"

class CallInfo {
private:
	std::string name;
	Function* function;
public:

	CallInfo(){}

	CallInfo(std::string name, Function* function):
		name(std::move(name)),
		function(std::move(function))
	{}

	std::string to_s(){
		return func::string_format("%s: %s", name.c_str(), function->to_s().c_str());
	}

	~CallInfo(){}

};

namespace NS_CallStack {
	static std::deque<CallInfo> calls;
}

class CallStack {
public:
	CallStack(){}

	static void clear(){
		NS_CallStack::calls.clear();
	}
	
	static void enter(std::string name, Function* function){
		NS_CallStack::calls.push_back(CallInfo(name, function));
	}

	static void exit(){
		NS_CallStack::calls.pop_back();
	}

	~CallStack(){}

};
#endif