#ifndef PARSER_H
#define PARSER_H

#include <vector>

class Parser {
private:
	Token TT_EOF_T = Token(TokenType::TT_EOF, "", -1, -1);
	std::vector<Token> tokens;
	int pos, size;
public:
	Parser(){}

	Parser(std::vector<Token> tokens):tokens(std::move(tokens)){
		pos = 0;
		size = this->tokens.size();
	}

	BlockStatement* parse();

	~Parser(){}
private:

	Statement* block();
	Statement* statementOrBlock();
	Statement* statement();
	Statement* assignment_statement();
	Statement* if_else();
	Statement* while_statement();
	Statement* do_while_statement();
	Statement* for_statement();
	FunctionDefineStatement* function_define(bool);


	FunctionalExpression* function();
	Expression* array();
	ArrayAccessExpression* element();
	Expression* expression();
	Expression* ternary();
	Expression* logicalOr();
	Expression* logicalAnd();
	Expression* bitwiseOr();
	Expression* bitwiseXor();
	Expression* bitwiseAnd();
	Expression* equality();
	Expression* conditional();
	Expression* shift();
	Expression* additive();
	Expression* multiplicative();
	Expression* unary();
	Expression* primary();


	Token consume(TokenType type);
	bool match(TokenType type);
	bool lookMatch(int pos, TokenType type);
	Token get(int rel_pos);

	void error_pars(std::string text, Token t);

};

#endif
