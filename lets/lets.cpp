//
//  lets.cpp
//  lets
//
//  Created by Dragan Stepan on 16.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/lets.hpp"
#include "../include/s_block_stat.hpp"
#include "../include/s_break_stat.hpp"
#include "../include/s_continue_stat.hpp"
#include "../include/s_return_stat.hpp"
#include "../include/l_variables.h"
#include "../include/l_functions.hpp"
#include "../include/l_string_value.hpp"
#include "../include/tools.hpp"
#include "../include/utils/minifier.hpp"

#define SHOW_LETS_ERROR_EXCEPTIONS(VAR, MESS) \
	show_lets_error("Error", Lets::current_file_name, to_str(VAR->get_position_row()), to_str(VAR->get_position_col()), MESS)

const lets_str_t Lets::VERSION = "0.0.1";
lets_str_t Lets::current_file_name = "go.lets";
Options Lets::options = Options();

void Lets::init(int argc, const char** argv){
	bool command_line_script = false;
	bool minifier_mode = false;
	if (argc == 1) {
		try {
			options.show_ast = false;
			options.show_tokens = false;
			options.show_measurements = false;
			options.optimization_level = 0;
			Lets::run(f2s(Lets::current_file_name));
		} catch (std::exception& e) {
			lets_output("Lets version " + VERSION + "\n\n" +
				"Usage: lets [options]\n" +
				"  options:\n" +
				"      -f, --file [input]  Run program file. Required.\n" +
				"      -o N, --optimize N  Perform optimization with N passes\n" +
				"      -m,  --minify        Minify source code\n" +
				"      -e   'command'       One line of script\n" +
				"      -a,  --showast       Show AST of program\n" +
				"      -tn, --showtokens   Show lexical tokens\n" +
				"      -t,  --showtime      Show elapsed time of parsing and execution");
		}
		return;
	}

	lets_str_t input = "";
	for (int i = 1; i < argc; i++) {
		if(lets_str_t(argv[i]) == "-a" || lets_str_t(argv[i]) == "--showast"){
			Lets::options.show_ast = true;
		} else if(lets_str_t(argv[i]) == "-m" || lets_str_t(argv[i]) == "--minify"){
			minifier_mode = true;
		} else if(lets_str_t(argv[i]) == "-tn" || lets_str_t(argv[i]) == "--showtokens"){
			Lets::options.show_tokens = true;
		} else if(lets_str_t(argv[i]) == "-t" || lets_str_t(argv[i]) == "--showtime"){
			Lets::options.show_measurements = true;
		} else if(lets_str_t(argv[i]) == "-o" || lets_str_t(argv[i]) == "--optimize"){
			if (i + 1 < argc) {
				try{
					Lets::options.optimization_level = std::stoi(argv[i + 1]);
				} catch (std::exception& e) {
					Lets::options.optimization_level = 2;
				}
				i++;
			} else {
				Lets::options.optimization_level = 2;
			}
		} else if(lets_str_t(argv[i]) == "-e"){
			command_line_script = true;
			Lets::current_file_name = "line";
			input = argv[i + 1];
			i++;
		} else if(lets_str_t(argv[i]) == "-f" || lets_str_t(argv[i]) == "--file"){
			if (i + 1 < argc) {
				Lets::current_file_name = argv[i + 1];
				input = f2s(Lets::current_file_name);
				i++;
			}
		} else {
			if (input == "") {
				Lets::current_file_name = argv[i];
				input = f2s(Lets::current_file_name);
			}
		}
	}

	if(!command_line_script)
		Lets::init_vars_file(NS_Tools::get_path(Lets::current_file_name));
	if(minifier_mode){
		lets_output(Minifier::minify(input))
		return;
	}

	Lets::run(input);
}

void Lets::run(lets_str_t input){
	TimeMeasurement measurement;
	Statement* programm;
	Statement* parsed_program;
	lets_vector_t<Token> tokens;

	measurement.start("Tokenize time");
	tokens = Lets::tokenize(input, true);
	measurement.stop("Tokenize time");
	if(Lets::options.show_tokens) for(auto t : tokens) lets_output(t.to_s())

	measurement.start("Parse time");
	parsed_program = Lets::parse(tokens, true);
	measurement.stop("Parse time");
	if(Lets::options.show_ast) lets_output(parsed_program->to_s())

	if(Lets::options.optimization_level > 0){
		measurement.start("Optimization time");
		programm = Optimizer::optimize(parsed_program, 10, true);
		measurement.stop("Optimization time");
	} else {
		programm = parsed_program;
	}

	Lets::init_functions();
	// programm->accept(programm, new FunctionAdder());
	// programm->accept(programm, new VariablesPrint());
	// programm->accept(programm, new AssignValidator());

	try{
		measurement.start("Execute time");
		programm->execute();
		measurement.stop("Execute time");
	} catch (ExecuteException& ee){
		show_lets_error(ee.head, ((ee.file_name != "") ? ee.file_name : Lets::current_file_name), to_str(ee.row), to_str(ee.col), ee.get_message())
	} catch (ReturnStatement*& rs){
		SHOW_LETS_ERROR_EXCEPTIONS(rs, "'" + rs->to_s() + "' statement not in function statement")
	} catch (BreakStatement*& bs){
		SHOW_LETS_ERROR_EXCEPTIONS(bs, "'" + bs->to_s() + "' statement not in loop statement")
	} catch (ContinueStatement*& cs){
		SHOW_LETS_ERROR_EXCEPTIONS(cs, "'" + cs->to_s() + "' statement not in loop statement")
	}

	if(Lets::options.show_measurements){
		lets_output(measurement.summary("s", true));
	}
}

lets_vector_t<Token> Lets::tokenize(const lets_str_t& input, bool stop = false){
	try{
		return (Lexer(input)).tokenize();
	} catch(LexerException& le){
		if(stop){
			show_lets_error(le.head, Lets::current_file_name, to_str(le.row), to_str(le.col), le.get_message())
		} else{
			throw le;
		}
	}
}

Statement* Lets::parse(const lets_vector_t<Token>& tokens, bool stop = false){
	try {
		return (Parser(tokens)).parse();
	} catch (ParseException& pe){
		if(stop){
			show_lets_error(pe.head, Lets::current_file_name, to_str(pe.row), to_str(pe.col), pe.get_message())
		} else{
			throw pe;
		}
	}
}

void Lets::init_functions(){
	class LetsBootFuncs :  public Function{
	public:
		LetsBootFuncs(){}
		~LetsBootFuncs(){}
		Value* execute(FUNCS_ARGS args){
			if(args.size() >= 1)
				std::cout << args[0]->as_string();
			lets_str_t i;
			getline(std::cin, i);
			return new StringValue(i);
		}
		lets_str_t to_s(){
			return "input()";
		}
	};

	Functions::set_lets_funcs("input", new LetsBootFuncs(), true);
}

void Lets::init_vars_file(lets_str_t path_file){
	Variables::define_lets("__file__", new StringValue(path_file), true);
	Variables::define_lets("__dir__", new StringValue(NS_Tools::splitpath(path_file)), true);
}

lets_str_t Lets::f2s(lets_str_t filename){
	lets_str_t input;
	std::ifstream inf;

	inf.open(filename);

	if (!inf) {
		throw std::runtime_error("Cannot open file " + filename);
		return "";
	}

	getline(inf, input, '\0');
	inf.close();

	return input;
}