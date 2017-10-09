#ifndef USE_STATEMENT_H
#define USE_STATEMENT_H

#include "../../include/modules_cpp.h"

class UseStatement : public Statement{
public:
	std::string name;

	UseStatement(std::string name):name(std::move(name)){}

	void execute(){
		if(name == "std") NS_LM_Std::run();
		else if(name == "math") NS_LM_Math::run();
		else if(name == "type") NS_LM_Type::run();
		else
			throw ParseException("Does not found module " + name);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return "use " + name;
	}

	~UseStatement(){}
};

#endif
