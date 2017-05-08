#include "main.h"

using namespace std;

void Lets(string input);

int main(int argc, char const *argv[]){

	string input;
	ifstream inf;
	inf.open ( "programm.lets" );//if (!inf)cerr
	getline ( inf, input, '\0' );
	inf.close();

	// cout << argc << endl;

	Lets(input);

	return 0;
}

void Lets(string input){

	Lexer lexer = Lexer_i(input); 
	vector<Token> tokens = Lexer_tokenize(&lexer);
	// for(Token tk : tokens) cout << tk.to_s() << endl;
	try{

		Parser parser = Parser(tokens);
		Statement* programm = parser.parse();
		// cout << programm->to_s() << endl;
		programm->accept(new FunctionAdder());
		// programm->accept(new VariablesPrint());
		programm->accept(new AssignValidator());
		programm->execute();

	} catch (ParseException pe){

		error(pe.message);

	}
}