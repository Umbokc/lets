#ifndef FUNCTIONDEFINESTATEMENT_H
#define FUNCTIONDEFINESTATEMENT_H

FunctionDefineStatement::FunctionDefineStatement(std::string name, std::vector<std::string> argNames, Statement *body){
	this->name = name;
	this->argNames = argNames;
	this->body = body;
}

void FunctionDefineStatement::execute(){
	Functions::set(name, new UserDefineFunction(argNames, body));
}

void FunctionDefineStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string FunctionDefineStatement::to_s(){
	std::string result = "def " + name + " ( ";
	
	for (std::string argument : argNames){
		result += argument;
		result +=  ", ";
	}

	result += "\b\b ) ";
	
	result += body->to_s();

	return result;
}

#endif
