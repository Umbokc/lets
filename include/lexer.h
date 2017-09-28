#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <regex>
#include <map>

namespace NS_Lexer{
	static std::string OPERATORS_CHARS = "+-*/%()[]{}=<>!&|,^~?:.@";

	static std::map<std::string, TokenType> OPERATORS = {
		{"+", TokenType::TT_PLUS},
		{"-", TokenType::TT_MINUS},
		{"*", TokenType::TT_STAR},
		{"/", TokenType::TT_SLASH},
		{"%", TokenType::TT_PERCENT},
		{"(", TokenType::TT_LPAREN},
		{")", TokenType::TT_RPAREN},
		{"[", TokenType::TT_LBRACKET},
		{"]", TokenType::TT_RBRACKET},
		{"{", TokenType::TT_LBRACE},
		{"}", TokenType::TT_RBRACE},
		{"=", TokenType::TT_EQ},
		{"<", TokenType::TT_LT},
		{">", TokenType::TT_GT},
		{",", TokenType::TT_COMMA},
		{".", TokenType::TT_DOT},
    {"^", TokenType::TT_CARET},
    {"~", TokenType::TT_TILDE},
    {"?", TokenType::TT_QUESTION},
    {":", TokenType::TT_COLON},
    
    {"!", TokenType::TT_EXCL},
    {"&", TokenType::TT_AMP},
    {"|", TokenType::TT_BAR},
    
    {"==", TokenType::TT_EQEQ},
    {"!=", TokenType::TT_EXCLEQ},
    {"<=", TokenType::TT_LTEQ},
    {">=", TokenType::TT_GTEQ},
    
    {"+=", TokenType::TT_PLUSEQ},
    {"-=", TokenType::TT_MINUSEQ},
    {"*=", TokenType::TT_STAREQ},
    {"/=", TokenType::TT_SLASHEQ},
    {"%=", TokenType::TT_PERCENTEQ},
    {"&=", TokenType::TT_AMPEQ},
    {"^=", TokenType::TT_CARETEQ},
    {"|=", TokenType::TT_BAREQ},
    {"::=", TokenType::TT_COLONCOLONEQ},

    {"++", TokenType::TT_PLUSPLUS},
    {"--", TokenType::TT_MINUSMINUS},
    
    {"::", TokenType::TT_COLONCOLON},
    
    {"&&", TokenType::TT_AMPAMP},
    {"||", TokenType::TT_BARBAR},
    
    {"<<", TokenType::TT_LTLT},
    {">>", TokenType::TT_GTGT},

    {"@", TokenType::TT_AT},
    {"@=", TokenType::TT_ATEQ},
    {"..", TokenType::TT_DOTDOT},
    {"**", TokenType::TT_STARSTAR},
    {"?:", TokenType::TT_QUESTIONCOLON}
	};

	static std::map<std::string, TokenType> KEYWORDS = {
		{"print", TokenType::TT_PRINT},
		{"put", TokenType::TT_PUT},
		{"if", TokenType::TT_IF},
		{"else", TokenType::TT_ELSE},
		// {"elif", TokenType::TT_ELIF},
		{"while", TokenType::TT_WHILE},
		{"for", TokenType::TT_FOR},
		{"do", TokenType::TT_DO},
		{"break", TokenType::TT_BREAK},
		{"continue", TokenType::TT_CONTINUE},
		{"def", TokenType::TT_DEF},
		{"def_c", TokenType::TT_DEF_C},
		{"return", TokenType::TT_RETURN},
		{"use", TokenType::TT_USE},
		{"end", TokenType::TT_END},
		{"in", TokenType::TT_IN},
		{"input", TokenType::TT_INPUT},
		{"include", TokenType::TT_RETURN}
	};
}

class Lexer {
private:
	std::string input, buffer;
	std::vector<Token> tokens;
	int pos, row, col, length;
public:
	Lexer(){}
	Lexer& operator=(const Lexer& r){return *this;}
	
	Lexer(const std::string& i) :input(std::move(i)) {
		pos = 0;
		row = 1;
		col = 1;
		length = i.length();
	}
	std::vector<Token> tokenize();

	~Lexer(){}

private:

	void tokenize_number();
	void tokenize_hex_number();
	int is_hex_number(char c);
	void tokenize_binary_number();
	void tokenize_word();
	void tokenize_text_double_quote();
	void tokenize_text_single_quote();
	void tokenize_operator();
	void tokenize_comment();
	void tokenize_multiline_comment();
	
	bool look_char(int rpos, char chr);
	char next();
	char peek(int rpos);

	// bool map_key_exists(std::map<std::string, TokenType> &the_map, std::string key);

	void clear_buffer();
	bool is_word_var(char);
	void add_token(TokenType tt);
	void add_token(TokenType tt, std::string txt);

	void lexer_error(std::string mess);
};

#endif