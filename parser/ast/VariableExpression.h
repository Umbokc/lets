#ifndef VARIABLEXPRESSION_H
#define VARIABLEXPRESSION_H


class VariableExpression : public Expression{
private:
	std::string name;
public:

	VariableExpression(std::string name){
		this->name = name;
	}

	Value* eval(){
		if(!Variables::isExists(name)) throw runtime_error("Variable does not exists");
		return Variables::get(name);
	}

	std::string to_s(){ 
		return name;
		// return name + "[" + Variables::get(name)->asString() + "]";
		// return name + "[" + dtos(Variables::get(name)->asNumber()) + "]";
	}
	~VariableExpression();
};

VariableExpression::~VariableExpression(){
}

#endif
