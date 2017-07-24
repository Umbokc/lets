#include "main.h"

int main(int argc, char const *argv[]) {
	
	if(argc <= 1){
		std::cout << "Give me code!" << std::endl;
		exit(1);
	}

	for (int i = 1; i < argc; ++i) {
		if(argc > 2)
			std::cout << "File: " << argv[i] << std::endl;

		Lets lets = Lets(func::f2s(argv[i]));
		lets.lexer(0);
		lets.parser(0);

	}

	return 0;
}