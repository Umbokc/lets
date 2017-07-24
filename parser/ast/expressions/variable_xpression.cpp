#ifndef VARIABLE_XPRESSION_H
#define VARIABLE_XPRESSION_H

class VariableExpression : public Expression{
public:
	std::string name;

	VariableExpression(std::string name):name(std::move(name)){}

	Value* eval(){
		if(!Variables::is_exists(name)) throw ParseException("Variable \"" + name + "\" does not exists");
		return Variables::get(name);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){ 
		return name;
	}

	~VariableExpression();
};

#endif
