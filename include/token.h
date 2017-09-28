#include <string>
#include "tokentype.h"

class Token {
private:
	TokenType type;
	std::string text;
	int row, col;
public:
	Token(){}
	// Token(const Token& t){}
	Token& operator=(const Token& t){return *this;}

	Token(const TokenType& tt, const std::string& txt,
				const int& r, const int& c)
				:type(std::move(tt)), text(std::move(txt)),
				 row(std::move(r)), col(std::move(c)){}

	// type get/set
	TokenType get_type(){ return type; }
	void set_type(const TokenType& type){ this->type = type; }

	// test get/set
	std::string get_text(){ return text; }
	void set_text(const std::string& text){ this->text = text; }

	// convert to string need data (token and text)
	std::string to_s(){ 
		return (TokenToString(this->type) + " " + text); 
	}

	int get_row() {
		return row;
	}

	int get_col() {
		return col;
	}

	std::string get_position() {
		return "[" + std::to_string(row) + ":" + std::to_string(col) + "]";
	}

	~Token(){}
};