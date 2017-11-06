//
//  main.cpp
//  lets
//
//  Created by Dragan Stepan on 29.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/main.h"
#include "../include/lets.hpp"
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/u_time_measurement.hpp"
#include "../include/ex_parse.h"

// #include "../include/visitors/function_adder.h"
// #include "../include/visitors/variables_print.h"
// #include "../include/visitors/assign_validator.h"

#include "../include/optimization/optimizer.h"

#define show_tokens(ts) for(auto t : ts) lets_output(t.to_s()) 

int main(int argc, const char * argv[]) {

	lets_str_t file = argv[1];
	TimeMeasurement measurement;
	Statement* programm;

	measurement.start("Tokenize time");
	Lexer l = Lexer(f2s(file));
	lets_vector_t<Token> tokens = l.tokenize();
	measurement.stop("Tokenize time");

	// show_tokens(tokens)

	measurement.start("Parse time");
	Parser parser = Parser(tokens);
	Statement* parsedProgram = parser.parse();
	measurement.stop("Parse time");

	if(false){
		measurement.start("Optimization time");
		programm = Optimizer::optimize(parsedProgram, 10, true);
		measurement.stop("Optimization time");
	} else {
		programm = parsedProgram;
	}


	try {
		
		// programm->accept(programm, new FunctionAdder());
		// programm->accept(programm, new VariablesPrint());
		// programm->accept(programm, new AssignValidator());

		measurement.start("Execute time");
		programm->execute();
		measurement.stop("Execute time");

	} catch (ParseException& pe){
		lets_output("Parser error: " << pe.get_message())
	}

	// lets_output(measurement.summary("s", true));

	return 0;
}

lets_str_t f2s(lets_str_t filename){
	lets_str_t input;
	std::ifstream inf;
	
	inf.open(filename);
	
	if (!inf) {
		std::cout << "Cannot open file" << std::endl;
		exit(1);
	}
	
	getline(inf, input, '\0');
	inf.close();
	
	return input;
}
