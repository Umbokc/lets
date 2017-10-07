#include "main.h"

int main(int argc, char const *argv[]) {

	if(argc <= 1){
		std::cout << "Give me code!" << std::endl;
		exit(1);
	}

	for (int i = 1; i < argc; ++i) {
		if(argc > 2)
			std::cout << "File: " << argv[i] << std::endl;

		TimeMeasurement measurement;

		measurement.start("Tokenize time");
		
		Lexer l = Lexer(func::f2s(argv[i]));
		std::vector<Token> tokens = l.tokenize();

		measurement.stop("Tokenize time");


		measurement.start("Parse time");

		Parser parser = Parser(tokens);
		Statement* programm = parser.parse();

		measurement.stop("Parse time");
		
		// programm->accept(new FunctionAdder());
		// programm->accept(new VariablesPrint());
		// programm->accept(new AssignValidator());

		try {
			measurement.start("Execute time");
			programm->execute();
			measurement.stop("Execute time");

		} catch (ParseException& pe){
			std::cout << "Parser error: " << pe.get_message() << std::endl;
		}

		// std::cout << measurement.summary("milliseconds", true) << std::endl;
	}

	return 0;
}