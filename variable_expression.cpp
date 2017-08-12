#ifndef VARIABLE_XPRESSION_H
#define VARIABLE_XPRESSION_H

class VariableExpression : public Expression, public Accessible{
// class VariableExpression : public AccessExpr{
public:
	std::string name;

	VariableExpression(std::string name):name(std::move(name)){}

	Value* eval(){
		return get();
	}
	
	Value* get(){
		if(!Variables::is_exists(name)) throw VariableDoesNotExistsException(name);
		return Variables::get(name);
	}
	
	Value* set(Value* value){
		Variables::set(name, value);
		return value;
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
