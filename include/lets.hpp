//
//  include/lets.hpp
//  lets
//
//  Created by Dragan Stepan on 29.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lets_hpp
#define include__lets_hpp

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "main.h"
#include "lexer.hpp"
#include "parser.hpp"
#include "utils/time_measurement.hpp"

#include "exception/lexer.h"
#include "exception/parse.h"
#include "exception/execute.h"

#define show_error(HEAD, MESS) \
	lets_output(HEAD << ":\n"  << MESS) \
	exit(1);

#define show_lets_error(HEAD, FILE_NAME, ROW, COL, MESS) \
	show_error("" << (HEAD == "" ? "Error" : HEAD) << "", FILE_NAME << ":[" << ROW << ":" << COL << "]: " << MESS) \
	exit(1);

typedef struct Options {
	bool show_tokens, show_ast, show_measurements;
	int optimization_level;

	Options() {
		show_tokens = false;
		show_ast = false;
		show_measurements = false;
		optimization_level = 0;
	}
} Options;

class Lets {
private:
	static lets_vector_t<lets_str_t> lets_args;
	static Options options;
public:
	static lets_str_t current_file_name;
	static const lets_str_t VERSION;
	static bool ModeFunctionAdder;

	static void init(int, const char**);
	static void run(lets_str_t);
	static lets_vector_t<Token> tokenize(const lets_str_t&, bool);
	static Statement* parse(const lets_vector_t<Token>&, bool);
	static lets_str_t f2s(lets_str_t);
	static void init_functions();
	static void init_vars_file(lets_str_t);
};

#endif /* include__lets_hpp */
