#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"

BlockStatement* Parser::parse(){
	BlockStatement* result = new BlockStatement();

	while(!match(TokenType::TT_EOF)){
		result->add(statement());
	}

	return result;
}

Statement* Parser::block(){
	BlockStatement* block = new BlockStatement();
	
	consume(TokenType::TT_LBRACE);
	while(!match(TokenType::TT_RBRACE)){
		block->add(statement());
	}

	return block;
}

Statement* Parser::statementOrBlock(){
	if(lookMatch(0, TokenType::TT_LBRACE)) return block();
	return statement();
}

Statement* Parser::statement(){
	if(match(TokenType::TT_PRINT)) 		return new PrintStatement(expression());
	if(match(TokenType::TT_PRINTLN)) 	return new PrintlnStatement(expression());
	if(match(TokenType::TT_IF)) 			return if_else();
	if(match(TokenType::TT_DO)) 			return do_while_statement();
	if(match(TokenType::TT_WHILE)) 		return while_statement();
	if(match(TokenType::TT_BREAK)) 		return new BreakStatement();
	if(match(TokenType::TT_CONTINUE)) return new ContinueStatement();
	if(match(TokenType::TT_RETURN)) 	return new ReturnStatement(expression());
	if(match(TokenType::TT_USE)) 			return new UseStatement(expression()->eval()->as_string());
	if(match(TokenType::TT_FOR)) 			return for_statement();
	if(match(TokenType::TT_DEF)) 			return function_define(false);
	if(match(TokenType::TT_DEF_C)) 		return function_define(true);
	if (lookMatch(0, TokenType::TT_WORD) && lookMatch(1,TokenType::TT_LPAREN)) {
		return new FunctionStatement(function());	
	}

	return assignment_statement();
}

Statement* Parser::assignment_statement(){
	// WORD EQ
	if(lookMatch(0, TokenType::TT_WORD) && lookMatch(1, TokenType::TT_EQ)){
		string var = consume(TokenType::TT_WORD).get_text();
		consume(TokenType::TT_EQ);
		return new AssignmentStatement(var, expression());
	}
	
	if(lookMatch(0,TokenType::TT_WORD) && lookMatch(1, TokenType::TT_LBRACKET)){
		ArrayAccessExpression* array = element();
		consume(TokenType::TT_EQ);
		return new ArrayAssignmentStatement(array, expression());
	}

	error_pars("Unknown statement", get(0));
	exit(1);
}

Statement* Parser::if_else(){

	Expression* condition = expression();
	Statement* ifStatement = statementOrBlock();
	Statement* elseStatemen;

	if(match(TokenType::TT_ELSE)){
		elseStatemen = statementOrBlock();
	} else {
		elseStatemen = NULL;
	}

	return new IfStatement(condition, ifStatement, elseStatemen);
}

Statement* Parser::while_statement(){
	Expression* condition = expression();
	Statement* statement = statementOrBlock();
	return new WhileStatement(condition, statement);
}

Statement* Parser::do_while_statement(){
	Statement* statement = statementOrBlock();
	consume(TokenType::TT_WHILE);
	Expression* condition = expression();
	return new DoWhileStatement(condition, statement);
}

Statement* Parser::for_statement(){

	match(TokenType::TT_LPAREN); // не обязательные скобки

	Statement* initialization = assignment_statement();
	consume(TokenType::TT_COMMA);
	Expression* termintion = expression();
	consume(TokenType::TT_COMMA);
	Statement* incement = assignment_statement();

	match(TokenType::TT_RPAREN); // не обязательные скобки

	Statement* statement = statementOrBlock();

	return new ForStatement(initialization, termintion, incement, statement);
}

FunctionDefineStatement* Parser::function_define(bool is_constexpr){
	std::string name = consume(TokenType::TT_WORD).get_text();
	consume(TokenType::TT_LPAREN);
	std::vector<std::string> arg_names;

	while(!match(TokenType::TT_RPAREN)){
		arg_names.push_back(consume(TokenType::TT_WORD).get_text());
		match(TokenType::TT_COMMA);
	}

	Statement* body = statementOrBlock();

	return new FunctionDefineStatement(name, arg_names, body, is_constexpr);
}

FunctionalExpression* Parser::function(){

	std::string name = consume(TokenType::TT_WORD).get_text();
	consume(TokenType::TT_LPAREN);

	FunctionalExpression* function = new FunctionalExpression(name);

	while(!match(TokenType::TT_RPAREN)){
		function->add_arguments(expression());
		match(TokenType::TT_COMMA);
	}

	return function; 
}

Expression* Parser::array(){
	consume(TokenType::TT_LBRACKET);

	std::vector<Expression* > elements;

	while(!match(TokenType::TT_RBRACKET)){
		elements.push_back(expression());
		match(TokenType::TT_COMMA);
	}

	return new ArrayExpression(elements);
}

ArrayAccessExpression* Parser::element(){
	string variable = consume(TokenType::TT_WORD).get_text();
	std::vector<Expression*> indices;

	do{
		consume(TokenType::TT_LBRACKET);
		indices.push_back(expression());
		consume(TokenType::TT_RBRACKET);
	} while(lookMatch(0, TokenType::TT_LBRACKET));

	return new ArrayAccessExpression(variable, indices);
}

Expression* Parser::expression(){
	return ternary();
}

Expression* Parser::ternary() {
	Expression* result = logicalOr();

	if (match(TokenType::TT_QUESTION)) {
		Expression* trueExpr = expression();
		consume(TokenType::TT_COLON);
		Expression* falseExpr = expression();
		return new TernaryExpression(result, trueExpr, falseExpr);
	}

	return result;
}

Expression* Parser::logicalOr(){
	Expression* result = logicalAnd();
	while(true){
		if(match(TokenType::TT_BARBAR)){
			result = new ConditionalExpression(ConditionalOperator::Operator::OR, result, logicalAnd());
			continue;
		}
		break;
	}
	return result;
}

Expression* Parser::logicalAnd(){
	Expression* result = bitwiseOr();
	while(true){
		if(match(TokenType::TT_AMPAMP)){
			result = new ConditionalExpression(ConditionalOperator::Operator::AND, result, bitwiseOr());
			continue;
		}
		break;
	}
	return result;
}

Expression* Parser::bitwiseOr() {

	Expression* expression = bitwiseXor();

	while (true) {
		if (match(TokenType::TT_BAR)) {
			expression = new BinaryExpression(BinaryOperator::Operator::OR, expression, bitwiseXor());
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::bitwiseXor() {
	Expression* expression = bitwiseAnd();

	while (true) {
		if (match(TokenType::TT_CARET)) {
			expression = new BinaryExpression(BinaryOperator::Operator::XOR, expression, bitwiseAnd());
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::bitwiseAnd() {
	Expression* expression = equality();

	while (true) {
		if (match(TokenType::TT_AMP)) {
			expression = new BinaryExpression(BinaryOperator::Operator::AND, expression, equality());
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::equality(){
	Expression* result = conditional();
	
	if(match(TokenType::TT_EQEQ)){
		return new ConditionalExpression(ConditionalOperator::Operator::EQUALS, result, conditional());
	}
	if(match(TokenType::TT_EXCLEQ)){
		return new ConditionalExpression(ConditionalOperator::Operator::NOT_EQUALS, result, conditional());
	}

	return result;
}

Expression* Parser::conditional(){
	Expression* result = shift();

	while(true){
		if(match(TokenType::TT_LT)){
			result = new ConditionalExpression(ConditionalOperator::Operator::LT, result, shift());
			continue;
		}
		if(match(TokenType::TT_LTEQ)){
			result = new ConditionalExpression(ConditionalOperator::Operator::LTEQ, result, shift());
			continue;
		}
		if(match(TokenType::TT_GT)){
			result = new ConditionalExpression(ConditionalOperator::Operator::GT, result, shift());
			continue;
		}
		if(match(TokenType::TT_GTEQ)){
			result = new ConditionalExpression(ConditionalOperator::Operator::GTEQ, result, shift());
			continue;
		}
		break;
	}
	
	return result;
}

Expression* Parser::shift() {
	Expression *expression = additive();

	while (true) {
		if (match(TokenType::TT_LTLT)) {
			expression = new BinaryExpression(BinaryOperator::Operator::LSHIFT, expression, additive());
			continue;
		}
		if (match(TokenType::TT_GTGT)) {
			expression = new BinaryExpression(BinaryOperator::Operator::RSHIFT, expression, additive());
			continue;
		}
		if (match(TokenType::TT_GTGTGT)) {
			expression = new BinaryExpression(BinaryOperator::Operator::URSHIFT, expression, additive());
			continue;
		}
		// if (match(TokenType::TT_DOTDOT)) {
		// 	expression = new BinaryExpression(BinaryOperator::Operator::RANGE, expression, additive());
		// 	continue;
		// }
		break;
	}

	return expression;
}

Expression* Parser::additive(){
	Expression *result = multiplicative();

	while (true) {
		if (match(TokenType::TT_PLUS)) {
			result = new BinaryExpression(BinaryOperator::Operator::ADD, result, multiplicative());
			continue;
		}
		if (match(TokenType::TT_MINUS)) {
			result = new BinaryExpression(BinaryOperator::Operator::SUBTRACT, result, multiplicative());
			continue;
		}
		// if (match(TokenType::TT_COLONCOLON)) {
		// 	result = new BinaryExpression(BinaryOperator::Operator::PUSH, result, multiplicative());
		// 	continue;
		// }
		// if (match(TokenType::TT_AT)) {
		// 	result = new BinaryExpression(BinaryOperator::Operator::AT, result, multiplicative());
		// 	continue;
		// }
		break;
	}

	return result;
}

Expression* Parser::multiplicative(){
	Expression *result = unary();

	while (true) {
		if (match(TokenType::TT_STAR)) {
			result = new BinaryExpression(BinaryOperator::Operator::MULTIPLY, result, unary());
			continue;
		}
		if (match(TokenType::TT_SLASH)) {
			result = new BinaryExpression(BinaryOperator::Operator::DIVIDE, result, unary());
			continue;
		}
		if (match(TokenType::TT_PERCENT)) {
			result = new BinaryExpression(BinaryOperator::Operator::REMAINDER, result, unary());
			continue;
		}
		// if (match(TokenType::TT_STARSTAR)) {
		// 	result = new BinaryExpression(BinaryOperator::Operator::POWER, result, unary());
		// 	continue;
		// }
		break;
	}

	return result;
}

Expression* Parser::unary(){
	if (match(TokenType::TT_PLUSPLUS)) {
		return new UnaryExpression(UnaryOperator::Operator::INCREMENT_PREFIX, primary());
	}
	if (match(TokenType::TT_MINUSMINUS)) {
		return new UnaryExpression(UnaryOperator::Operator::DECREMENT_PREFIX, primary());
	}
	if(match(TokenType::TT_MINUS)) {
		return new UnaryExpression(UnaryOperator::Operator::NEGATE, primary());
	}
	if (match(TokenType::TT_EXCL)) {
		return new UnaryExpression(UnaryOperator::Operator::NOT, primary());
	}
	if (match(TokenType::TT_TILDE)) {
		return new UnaryExpression(UnaryOperator::Operator::COMPLEMENT, primary());
	}
	if(match(TokenType::TT_PLUS)){
		return primary();
	}

	return primary();
}

Expression* Parser::primary() {
	Token current = this->get(0);

	if(match(TokenType::TT_NUMBER)){
		return new ValueExpression(atof(&current.get_text()[0u]));
	}
	if(match(TokenType::TT_HEX_NUMBER)){
		return new ValueExpression(std::stol(&current.get_text()[0u], 0, 16));
	}
	if(match(TokenType::TT_OCTAL_NUMBER)){
		return new ValueExpression(std::stol(&current.get_text()[0u], 0, 8));
	}
	if(match(TokenType::TT_BINARY_NUMBER)){
		return new ValueExpression(std::stol(&current.get_text()[0u], 0, 2));
	}
	if(lookMatch(0, TokenType::TT_WORD) && lookMatch(1, TokenType::TT_LPAREN)){
		return function();
	}
	if(lookMatch(0, TokenType::TT_WORD) && lookMatch(1,TokenType::TT_LBRACKET)){
		return element();
	}
	if(lookMatch(0,TokenType::TT_LBRACKET)){
		return array();
	}
	if(match(TokenType::TT_WORD)){
		return new VariableExpression(current.get_text());
	}
	if(match(TokenType::TT_TEXT)){
		return new ValueExpression(current.get_text());
	}
	if(match(TokenType::TT_LPAREN)){
		Expression* result = expression();
		match(TokenType::TT_RPAREN);
		return result;
	}

	error_pars("Unknown expression:", get(0));
	exit(1);
}

Token Parser::consume(TokenType type){

	Token current = get(0);

	if(type != current.get_type()){
		error_pars("Token " + std::to_string(current.get_type()) +
			" dosn't match " + TokenToString(type), current);
	}
	pos++;
	return current;
}

bool Parser::match(TokenType type){

	Token current = get(0);
	if(type != current.get_type()) return false;
	pos++;

	return true;
}

bool Parser::lookMatch(int pos, TokenType type) {
	return get(pos).get_type() == type;
}

Token Parser::get(int rel_pos){
	int position = pos + rel_pos;
	if(position >= size) return TT_EOF_T;
	return tokens[position];
}

void Parser::error_pars(std::string text, Token t){
	
	if(t.get_row() == -1 || t.get_col() == -1){
		t = get(-1);
	}

	// std::string expr_err = t.to_s();

	std::cout << "Parser error " << t.get_position() << ": " << text << std::endl; 
}

#endif
