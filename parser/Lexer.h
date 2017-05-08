#ifndef LEXER_H
#define LEXER_H

using namespace std;

static string OPERATOR_CHARS = "+-*/%()[]{}=<>!&|,^~?:";
static map<string, TokenType> OPERATORS = {
	{"+", _PLUS_},
	{"-", _MINUS_},
	{"*", _STAR_},
	{"/", _SLASH_},
	{"%", _PERCENT_},
	{"(", _LPAREN_},
	{")", _RPAREN_},
	{"[", _LBRACKET_},
	{"]", _RBRACKET_},
	{"{", _LBRACE_},
	{"}", _RBRACE_},
	{"=", _EQ_},
	{"<", _LT_},
	{">", _GT_},
	{",", _COMMA_},
	{"^", _CARET_},
	{"~", _TILDE_},
	{"?", _QUESTION_},
	{":", _COLON_},

	{"!", _EXCL_},
	{"&", _AMP_},
	{"|", _BAR_},

	{"==", _EQEQ_},
	{"!=", _EXCLEQ_},
	{"<=", _LTEQ_},
	{">=", _GTEQ_},

	{"&&", _AMPAMP_},
	{"||", _BARBAR_},

	{"<<", _LTLT_},
	{">>", _GTGT_},
	{">>>", _GTGTGT_},
};


typedef struct Lexer {
	string input;
	vector<Token> tokens;
	int pos;
	int row, col;
	int length;
}Lexer;


// declaration {
Lexer Lexer_i(string input);
vector<Token> Lexer_tokenize(Lexer *l);
void Lexer_tokenizeNumber(Lexer *l);
void Lexer_tokenizeHexNumber(Lexer *l);
int isHexNumber(char c);
void Lexer_tokenizeOperator(Lexer *l);
void Lexer_tokenizeWord(Lexer *l);
void Lexer_tokenizeText(Lexer *l);
void Lexer_tokenizeComment(Lexer *l);
void Lexer_tokenizeMultilineComment(Lexer *l);
char Lexer_next(Lexer *l);
char Lexer_peek(Lexer *l, int relPos);
void Lexer_addToken(Lexer *l, TokenType type);
void Lexer_addToken(Lexer *l, TokenType type, string text);
// declaration }
void error_lex(Lexer *l, string text) {
	error("["+ std::to_string(l->row) +":" + std::to_string(l->col) +"] " + text);
}

Lexer Lexer_i(string input){
	Lexer a;
	a.pos = 0;
	a.row = 1;
	a.col = 1;	
	a.input = input;
	a.length = input.length();
	return a;
}

vector<Token> Lexer_tokenize(Lexer *l){

	while(l->pos < l->length){
		char current = Lexer_peek(l, 0);
		if(isdigit(current)){
			Lexer_tokenizeNumber(l);

		} else if (isalpha(current, locale())){
			Lexer_tokenizeWord(l);

		} else if(current == '#'){
			Lexer_next(l);
			Lexer_tokenizeHexNumber(l);

		} else if(current == '"'){
			Lexer_tokenizeText(l);

		} else if(find_c(OPERATOR_CHARS, current) != -1){
			Lexer_tokenizeOperator(l);

		} else {
			Lexer_next(l);
		}
	}

	return l->tokens;
}

void Lexer_tokenizeNumber(Lexer *l){
	string buf = "";
	char current = Lexer_peek(l, 0);

	while(true){
		if (current == '.'){
			if (find_c(buf, '.') != -1) error_lex(l, "Invalid float number");
		} else if (!isdigit(current)){
			break;
		}
		buf.push_back(current);
		current = Lexer_next(l);
	}

	Lexer_addToken(l, _NUMBER_, buf);
}

void Lexer_tokenizeHexNumber(Lexer *l){
	string buf = "";
	char current = Lexer_peek(l, 0);

	while(isdigit(current) || isHexNumber(current) != -1){
		buf.push_back(current);
		current = Lexer_next(l);
	}

	Lexer_addToken(l, _HEX_NUMBER_, buf);
}

int isHexNumber(char c){
	string a = "abcdef";
	return find_c(a, tolower(c, locale()));
}

void Lexer_tokenizeOperator(Lexer *l){
	char current = Lexer_peek(l, 0);
	if(current == '/') {
		if(Lexer_peek(l, 1) == '/'){
			Lexer_next(l);
			Lexer_next(l);
			Lexer_tokenizeComment(l);
			return;
		} else if(Lexer_peek(l, 1) == '*'){
			Lexer_next(l);
			Lexer_next(l);
			Lexer_tokenizeMultilineComment(l);
			return;
		}
	}
	string buffer;
	while(true){
		string text = buffer;
		if((OPERATORS.find(text + current) == OPERATORS.end()) && !text.empty()){
			Lexer_addToken(l,OPERATORS[text]);
			return;
		}
		buffer.push_back(current);
		current = Lexer_next(l);
	}
}

void Lexer_tokenizeWord(Lexer *l){
	string buffer;
	char current = Lexer_peek(l,0);
	while(true){
		if(!(isdigit(current) || isalpha(current, locale())) && (current != '_') && (current != '$')){
			break;
		}
		buffer.push_back(current);
		current = Lexer_next(l);
	}


	const char *buf = buffer.c_str();
	switch(s2i(buf)){
		case s2i("print"): 		Lexer_addToken(l, _PRINT_); break;
		case s2i("if"): 			Lexer_addToken(l, _IF_); break;
		case s2i("else"): 		Lexer_addToken(l, _ELSE_); break;
		case s2i("while"): 		Lexer_addToken(l, _WHILE_); break;
		case s2i("for"): 			Lexer_addToken(l, _FOR_); break;
		case s2i("do"): 			Lexer_addToken(l, _DO_); break;
		case s2i("break"): 		Lexer_addToken(l, _BREAK_); break;
		case s2i("continue"): Lexer_addToken(l, _CONTINUE_); break;
		case s2i("def"): 			Lexer_addToken(l, _DEF_); break;
		case s2i("return"): 	Lexer_addToken(l, _RETURN_); break;
		case s2i("use"): 			Lexer_addToken(l, _USE_); break;
		default:
		Lexer_addToken(l, _WORD_, buffer); break;
	}

}

void Lexer_tokenizeText(Lexer *l){
	Lexer_next(l); // skip "
	string buffer;
	char current = Lexer_peek(l,0);
	while(true){
    if (current == '\0') error_lex(l, "Reached end of file while parsing text string.");
		if(current == '\\'){
			current = Lexer_next(l);
			switch(current){
				case '"': current = Lexer_next(l); buffer.push_back('"'); continue;
				case 'n': current = Lexer_next(l); buffer.push_back('\n'); continue;
				case 't': current = Lexer_next(l); buffer.push_back('\t'); continue;
			}
			buffer.push_back('\\');
			continue;
		}
		if(current == '"') break;

		buffer.push_back(current);
		current = Lexer_next(l);
	}
	Lexer_next(l); // skip closing "
	Lexer_addToken(l, _TEXT_, buffer);
}

void Lexer_tokenizeComment(Lexer *l){
	char current = Lexer_peek(l, 0);
	while(true){
		if(current == '\0' || current == '\n' || current == '\r') break;
		current = Lexer_next(l);
	}
}

void Lexer_tokenizeMultilineComment(Lexer *l){
	char current = Lexer_peek(l, 0);
	while(true){
		if(current == '\0') error_lex(l, "Reached end of file while parsing multiline comment");	
		if(current == '*' && Lexer_peek(l,1) == '/') break;
		current = Lexer_next(l);
	}
	Lexer_next(l); // *
	Lexer_next(l); // /
}

char Lexer_next(Lexer *l){
	l->pos++;
	char result = Lexer_peek(l, 0);
	
	if(result == '\n'){
		l->row++;
		l->col = 1;
	} else {
		l->col++;
	}

	return result;
}

char Lexer_peek(Lexer *l, int relPos){
	int position = l->pos + relPos;
	if(position >= l->length) return '\0';
	return l->input[position];
}

void Lexer_addToken(Lexer *l, TokenType type){
	Lexer_addToken(l, type, "");
}

void Lexer_addToken(Lexer *l, TokenType type, string text){
	l->tokens.push_back(Token(type, text, l->row, l->col));
}

#endif