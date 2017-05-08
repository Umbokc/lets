#ifndef TOKEN_H
#define TOKEN_H

class Token {
private:
	TokenType type;
	std::string text;
	int row, col;
public:
	Token();
	Token(TokenType type, std::string text, int row, int col) {
		this->type = type;
		this->text = text;
		this->row = row;
		this->col = col;
	}

	TokenType getType(){ return type; }
	void setType(TokenType type){ this->type = type; }

	std::string getText(){ return text; }
	void setText(std::string text){ this->text = text; }

	std::string to_s(){ 
		return (TokenTypeText[type] + " " + text); 
	}

	int getRow() {
		return row;
	}

	int getCol() {
		return col;
	}

	std::string position() {
		return "[" + std::to_string(row) + ":" + std::to_string(col) + "]";
	}

	~Token();
	
};

Token::~Token(){

}

#endif