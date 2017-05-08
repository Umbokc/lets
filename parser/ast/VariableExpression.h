#ifndef VARIABLEXPRESSION_H
#define VARIABLEXPRESSION_H

VariableExpression::VariableExpression(std::string name){
	this->name = name;
}

Value* VariableExpression::eval(){
	if(!Variables::isExists(name)) throw ParseException("Variable \"" + name + "\" does not exists");
	return Variables::get(name);
}

void VariableExpression::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string VariableExpression::to_s(){ 
	return name;
	// return name + "[" + Variables::get(name)->asString() + "]";
	// return name + "[" + dtos(Variables::get(name)->asNumber()) + "]";
}

#endif
