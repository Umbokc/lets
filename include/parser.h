#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <map>
#include <climits>
#include <string>

namespace NS_Parser{
	static std::map<TokenType, NS_Binary::Operator> ASSIGN_OPERATORS = {
		{TokenType::TT_EQ, NS_Binary::Operator::THE_NULL},
		{TokenType::TT_PLUSEQ, NS_Binary::Operator::ADD},
		{TokenType::TT_MINUSEQ, NS_Binary::Operator::SUBTRACT},
		{TokenType::TT_STAREQ, NS_Binary::Operator::MULTIPLY},
		{TokenType::TT_SLASHEQ, NS_Binary::Operator::DIVIDE},
		{TokenType::TT_PERCENTEQ, NS_Binary::Operator::REMAINDER},
		{TokenType::TT_AMPEQ, NS_Binary::Operator::AND},
		{TokenType::TT_CARETEQ, NS_Binary::Operator::XOR},
		{TokenType::TT_BAREQ, NS_Binary::Operator::OR},
		{TokenType::TT_LTLT, NS_Binary::Operator::LSHIFT},
		{TokenType::TT_GTGT, NS_Binary::Operator::RSHIFT},
		// {TokenType::TT_ATEQ, NS_Binary::Operator::AT}
	};
}

class Parser {
private:
	Token TT_EOF_T = Token(TokenType::TT_EOF, "", -1, -1);
	std::vector<Token> tokens;
	int pos, size;
	Statement* parsed_statement;
public:
	
	Parser(){}

	Parser(std::vector<Token> tokens):tokens(std::move(tokens)){
		pos = 0;
		size = this->tokens.size();
	}

	BlockStatement* parse();

	~Parser(){}
private:

	Statement* get_parsed_statement();

	Statement* block();
	Statement* statement_or_block();
	Statement* statement();
	Statement* assignment_statement();
	Statement* if_else();
	Statement* while_statement();
	Statement* do_while_statement();
	Statement* for_statement();
	ForeachStatement* foreach_arr_statement(bool);
	FunctionDefineStatement* function_define(bool);
	Arguments arguments();
	Statement* statement_body();

	Expression* function_chain(Expression*);
	FunctionalExpression* function(Expression*);
	Expression* array();
	Expression* map_vals();
	MatchExpression* match();
	Expression* expression();
	Expression* assignment();
	Expression* assignment_strict();
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
	Expression* primary(bool);
	Expression* variable(bool);
	Expression* qualified_name();
	std::vector<Expression*> variable_suffix();
	Expression* value();


	Token consume(TokenType);
	bool match(TokenType);
	bool match(std::vector<TokenType>);
	bool look_match(int, TokenType);
	Token get(int);

	void error_pars(std::string, Token);

};

#endif
