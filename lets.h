#ifndef LETS_H
#define LETS_H
#include <iostream>
#include <string>
#include <vector>

class Lets {
private:
	std::string input;
	std::vector<Token> tokens;
public:
	Lets(){}
	Lets& operator=(const Lets& r){return *this;}

	Lets(const std::string& input): input(std::move(input)){
	}

	void lexer(bool debag){
		Lexer l = Lexer(input);
		tokens = l.tokenize();

		if(debag){
			for(Token t : tokens) std::cout << t.to_s() << std::endl;
		}
	}
	
	void parser(bool debag){
		try {

			Parser parser = Parser(tokens);
			Statement* programm = parser.parse();
			if(debag){
				std::cout << programm->to_s() << std::endl;
			}
			// programm->accept(new FunctionAdder());
			// programm->accept(new VariablesPrint());
			// programm->accept(new AssignValidator());

			programm->execute();

		} catch (ParseException& pe){
			std::cout << "Parser error: " << pe.get_message() << std::endl; 
		}
	}
	
	~Lets(){}
};

#endif