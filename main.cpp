#include "main.h"

using namespace std;

int main(){

	string input;
	ifstream inf;
	inf.open ( "programm.lets" );//if (!inf)cerr
	getline ( inf, input, '\0' );
	inf.close();

	Lexer lexer = Lexer_i(input); 
	vector<Token> tokens = Lexer_tokenize(&lexer);
	// for(Token tk : tokens) cout << tk.to_s() << endl;

	Parser parser = Parser(tokens);
	Statement* programm = parser.parse();
	cout << programm->to_s() << endl;
	programm->execute();

	return 0;
}
