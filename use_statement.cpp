#ifndef USE_STATEMENT_H
#define USE_STATEMENT_H

#include "modules/cpp/std/std_module.h"
#include "modules/cpp/math/math_module.h"

class UseStatement : public Statement{
public:
	std::string name;

	UseStatement(std::string name):name(std::move(name)){}

	void execute(){
		if(name == "std") Lets_Module_Std::run();
		else if(name == "math") Lets_Module_Math::run();
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
