#include "main.h"

using namespace std;

int main(){

	string input;
	ifstream inf;
	inf.open ( "programm.lets" );//if (!inf)cerr
	getline ( inf, input, '\0' );
	inf.close();

	Lexer *lexer = new Lexer(input);
	vector<Token> tokens = lexer->tokenize();

	Parser *parser = new Parser(tokens);
	vector<Statement*> statements = parser->parse();

	// // tokens
	for(Token tk : tokens){
		cout << tk.to_s() << endl;
	}
	cout << "------------" << endl;

	// Statements
	for(auto st : statements){
		cout << st->to_s() << endl;
	}
	for(auto st : statements){
		st->execute();
	}

	// delete lexer;
	// delete parser;

	return 0;
}