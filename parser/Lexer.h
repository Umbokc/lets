#ifndef LEXER
#define LEXER

using namespace std;

static string OPERATOR_CHARS = "+-*/()=";
static TokenType OPERATOR_TOKENS[] = {
	_PLUS_, _MINUS_,
	_STAR_, _SLASH_,
	_LPAREN_, _RPAREN_,
	_EQ_
};

class Lexer{
private:
	string input;
	vector<Token> tokens;
	int pos;
	int length;
public:
	Lexer(string i): input(i){
		length = input.length();
	}

	vector<Token> tokenize(){
		while(pos < length){
			char current = peek(0);
			if(isdigit(current)) tokenizeNumber();
			else if(isalpha(current, locale())){				
				tokenizeWord();
			} 
			else if (current == '#'){
				next();
				tokenizeHexNumber();
			}
			else if (current == '"'){
				tokenizeText();
			} else if (OPERATOR_CHARS.find(current) != string::npos){
				tokenizeOperator();
			} else {
				// whitespaces
				next();
			}
		}
		return tokens;
	}

	~Lexer();
private:
	void tokenizeNumber(){
		string buffer;
		char current = peek(0);
		
		while(true){
			if(current == '.'){
				if(buffer.find(".") != string::npos) throw runtime_error("Invalid float number");
				
			} else if (!isdigit(current)){
				break;
			}

			buffer.push_back(current);
			current = next();
		}
		addToken(_NUMBER_, buffer);
	}

	void tokenizeHexNumber(){
		string buffer;
		char current = peek(0);
		
		while(isdigit(current) || isHexNumber(current)){
			buffer.push_back(current);
			current = next();
		}
		addToken(_HEX_NUMBER_, buffer);
	}

	bool isHexNumber(char current){
		string abcdef = "abcdef";
		return (abcdef.find(tolower(current, locale())) != string::npos);
	}

	void tokenizeOperator(){
		int position = OPERATOR_CHARS.find(peek(0));
		addToken(OPERATOR_TOKENS[position]);
		next();
	}

	void tokenizeWord(){
		string buffer;
		char current = peek(0);
		while(true){
			if (!(isdigit(current) || isalpha(current, locale())) && (current != '_') && (current != '$')){
				break;
			}
			buffer.push_back(current);
			current = next();
		}
		if(buffer == "print"){
			addToken(_PRINT_);
		} else {
			addToken(_WORD_, buffer);
		}
	}

	void tokenizeText(){
		next(); // skip "
		string buffer;
		char current = peek(0);
		while(true){
			if (current == '\\'){
				current = next();
				switch(current){
					case '"': current = next();buffer.push_back('"'); continue;
					case 'n': current = next();buffer.push_back('\n'); continue;
					case 't': current = next();buffer.push_back('\t'); continue;
				}
				buffer.push_back('\\');
				continue;
			}
			if (current == '"') break;
			buffer.push_back(current);
			current = next();
		}
		next(); // skip closing "
		addToken(_TEXT_, buffer);
	}

	char next (){
		pos++;
		return peek(0);
	}

	char peek(int relativePosition){
		int position = pos + relativePosition;
		if(position >= length) return '\0';
		return input[position];
	}

	void addToken(TokenType type) {
		addToken(type, "");
	}

	void addToken(TokenType type, string text) {
		tokens.push_back(Token(type, text));
	}
};

Lexer::~Lexer(){
		// delete[] tokens;
}

#endif