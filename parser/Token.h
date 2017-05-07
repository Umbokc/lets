#ifndef TOKEN_H
#define TOKEN_H

class Token {
private:
	TokenType type;
	std::string text;
public:
	Token();
	Token(TokenType type, std::string text){
		this->type = type;
		this->text = text;
	}

	TokenType getType(){ return type; }
	void setType(TokenType type){ this->type = type; }

	std::string getText(){ return text; }
	void setText(std::string text){ this->text = text; }

	std::string to_s(){ 
		return (TokenTypeText[type] + " " + text); 
	}


	~Token();
	
};

Token::~Token(){

}

#endif