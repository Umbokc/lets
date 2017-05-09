#include "main.h"
using namespace std;

void Lets(string);
string f2l(string);

int main(int argc, char const **argv){

  if(argc <= 1){
    error("Give me code!");
  }

  for (int i = 1; i < argc; ++i) {
    if(argc > 2)
      cout << "File: " << argv[i] << endl;
    Lets(f2l(argv[i]));
  }

  return 0;
}

string f2l(string filename){
  
  string input;
  ifstream inf;
  inf.open ( filename );

  if (!inf){
    error("Cannot open file");
  }

  getline ( inf, input, '\0' );
  inf.close();

  return input;
}

void Lets(string input){

  Lexer *lexer = new Lexer(input);
  vector<Token> tokens = lexer->tokenize();
  // for(Token tk : tokens) cout << tk.to_s() << endl;
  
  try {

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