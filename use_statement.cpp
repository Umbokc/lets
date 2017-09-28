#ifndef USE_STATEMENT_H
#define USE_STATEMENT_H

#include "modules/cpp/std/main.h"
#include "modules/cpp/math/main.h"
#include "modules/cpp/type/main.h"

class UseStatement : public Statement{
public:
	std::string name;

	UseStatement(std::string name):name(std::move(name)){}

	void execute(){
		if(name == "std") Lets_Module_Std::run();
		else if(name == "math") Lets_Module_Math::run();
		else if(name == "type") Lets_Module_Type::run();
		else
			throw ParseException("Does not found module " + name);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return "use " + name;
	}

	~UseStatement();
};

#endif
