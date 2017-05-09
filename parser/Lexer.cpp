#ifndef LEXER_CPP
#define LEXER_CPP

using namespace std;

class Lexer {
private:
	string input;
	vector<Token> tokens;
	int pos;
	int row, col;
	int length;
public:
	Lexer(){

	}
		
	Lexer(string input){
		this->pos = 0;
		this->row = 1;
		this->col = 1;	
		this->input = input;
		this->length = input.length();
	}

	vector<Token> tokenize(){

		while(this->pos < this->length){
			
			char current = peek(0);

			if(isdigit(current)){
				tokenizeNumber();

			} else if (isalpha(current, locale())){
				tokenizeWord();

			} else if(current == '#'){
				next();
				tokenizeHexNumber();

			} else if(current == '"'){
				tokenizeText();

			} else if(find_c(OPERATOR_CHARS, current) != -1){
				tokenizeOperator();

			} else {
				next();
			}
		}

		return this->tokens;
	}

	~Lexer();

private:

	void tokenizeNumber(){
		string buf = "";
		char current = peek(0);

		while(true){
			if (current == '.'){
				if (find_c(buf, '.') != -1) error_lex("Invalid float number");
			} else if (!isdigit(current)){
				break;
			}
			buf.push_back(current);
			current = next();
		}

		addToken(_NUMBER_, buf);
	}

	void tokenizeHexNumber(){
		string buf = "";
		char current = peek(0);

		while(isdigit(current) || isHexNumber(current) != -1){
			buf.push_back(current);
			current = next();
		}

		addToken(_HEX_NUMBER_, buf);
	}

	int isHexNumber(char c){
		string a = "abcdef";
		return find_c(a, tolower(c, locale()));
	}

	void tokenizeOperator(){
		char current = peek(0);
		if(current == '/') {
			if(peek(1) == '/'){
				next();
				next();
				tokenizeComment();
				return;
			} else if(peek(1) == '*'){
				next();
				next();
				tokenizeMultilineComment();
				return;
			}
		}
		string buffer;
		while(true){
			string text = buffer;
			if((OPERATORS.find(text + current) == OPERATORS.end()) && !text.empty()){
				addToken(OPERATORS[text]);
				return;
			}
			buffer.push_back(current);
			current = next();
		}
	}

	void tokenizeWord(){
		string buffer;
		char current = peek(0);
		while(true){
			if(!(isdigit(current) || isalpha(current, locale())) && (current != '_') && (current != '$')){
				break;
			}
			buffer.push_back(current);
			current = next();
		}


		const char *buf = buffer.c_str();
		switch(s2i(buf)){
			case s2i("print"): 		addToken(_PRINT_); break;
			case s2i("if"): 			addToken(_IF_); break;
			case s2i("else"): 		addToken(_ELSE_); break;
			case s2i("while"): 		addToken(_WHILE_); break;
			case s2i("for"): 			addToken(_FOR_); break;
			case s2i("do"): 			addToken(_DO_); break;
			case s2i("break"): 		addToken(_BREAK_); break;
			case s2i("continue"): addToken(_CONTINUE_); break;
			case s2i("def"): 			addToken(_DEF_); break;
			case s2i("return"): 	addToken(_RETURN_); break;
			case s2i("use"): 			addToken(_USE_); break;
			default:
			addToken(_WORD_, buffer); break;
		}
	}

	void tokenizeText(){
		next(); // skip "
		string buffer;
		char current = peek(0);
		while(true){
	    if (current == '\0') error_lex("Reached end of file while parsing text string.");
			if(current == '\\'){
				current = next();
				switch(current){
					case '"': current = next(); buffer.push_back('"'); continue;
					case 'n': current = next(); buffer.push_back('\n'); continue;
					case 't': current = next(); buffer.push_back('\t'); continue;
				}
				buffer.push_back('\\');
				continue;
			}
			if(current == '"') break;

			buffer.push_back(current);
			current = next();
		}
		next(); // skip closing "
		addToken(_TEXT_, buffer);
	}

	void tokenizeComment(){
		char current = peek(0);
		while(true){
			if(current == '\0' || current == '\n' || current == '\r') break;
			current = next();
		}
	}

	void tokenizeMultilineComment(){
		char current = peek(0);
		while(true){
			if(current == '\0') error_lex("Reached end of file while parsing multiline comment");	
			if(current == '*' && peek(1) == '/') break;
			current = next();
		}
		next(); // *
		next(); // /
	}

	char next(){
		this->pos++;
		char result = peek(0);
		
		if(result == '\n'){
			this->row++;
			this->col = 1;
		} else {
			this->col++;
		}

		return result;
	}

	char peek(int relPos){
		int position = this->pos + relPos;
		if(position >= this->length) return '\0';
		return this->input[position];
	}

	void addToken(TokenType type){
		addToken(type, "");
	}

	void addToken(TokenType type, string text){
		this->tokens.push_back(Token(type, text, this->row, this->col));
	}

	void error_lex(string text) {
		error("["+ std::to_string(row) +":" + std::to_string(col) +"] " + text);
	}
};

Lexer::~Lexer(){

}

#endif