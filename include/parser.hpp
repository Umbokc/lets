//
//  include/parser.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__parser_hpp
#define include__parser_hpp

#include <string>
#include <vector>
#include <map>
#include "main.h"

#include "declaration.h"

#include "tokentype.h"
#include "token.hpp"

#include "expression.h"
#include "statement.h"

#include "expressions/binary_expr.hpp"

class Parser {
private:
	Token TT_EOF_T = Token(TT_EOF, "EOF", 0, 0);
	lets_vector_t<Token> tokens;
	size_t pos, size;
	// Statement* parsed_statement;
public:

	static lets_map_t<u_tt_t, NS_Binary::Operator> ASSIGN_OPERATORS;

	Parser();
	Parser(lets_vector_t<Token>);

	BlockStatement* parse();

	~Parser() {}
private:

	// Statement* get_parsed_statement();

	Statement* block();
	Statement* block(u_tt_t);
	Statement* block(lets_vector_t<u_tt_t>);
	Statement* statement_or_block();
	Statement* statement_or_block(u_tt_t);

	Statement* statement();
	Statement* assignment_statement();
	Statement* multi_assignment_statement();
	Statement* if_else();
	Statement* while_statement();
	Statement* do_while_statement();
	Statement* for_statement();
	Statement* use_statement();
	ForeachStatement* foreach_arr_statement(size_t&, size_t&, bool);
	FunctionDefineStatement* function_define();
	Arguments arguments();
	Statement* statement_body();

	Expression* function_chain(Expression*);
	FunctionalExpression* function(Expression*);
	ClassExpression* class_expr();
	Expression* array();
	Expression* map_vals();
	MatchExpression* match();
	Expression* expression();
	Expression* assignment();
	Expression* assignment_strict();
	Expression* include_expression();
	Expression* in_expression();
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
	lets_vector_t<Expression*> variable_suffix();
	Expression* value();

	Token consume(u_tt_t);

	bool match(u_tt_t);
	bool match(lets_vector_t<u_tt_t>);

	bool look_match(int, u_tt_t);

	Token get(int);

	int find_c(lets_str_t, char);
	void error_pars(lets_str_t, Token);
};

#endif /* include__parser_hpp */
