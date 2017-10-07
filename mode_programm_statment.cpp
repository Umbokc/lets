#ifndef MODE_PROGRAMM_CPP
#define MODE_PROGRAMM_CPP
#include <string>

class ModeProgrammStatement : public Statement {
public:

	std::string name;

	ModeProgrammStatement(){}

	ModeProgrammStatement(std::string name):name(std::move(name)){}

	void execute(){
		if(this->name == "0x666"){
			Mode_Programm::without_stop = true;
		}
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		return this->name;
	}

	~ModeProgrammStatement(){}
};

#endif