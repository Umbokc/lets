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

Statement* Parser::block(int type){
	BlockStatement* block = new BlockStatement();

	consume(TokenType::TT_COLON);
	while(end_the_block(type)){
		block->add(statement());
	}

	return block;
}

Statement* Parser::statement_or_block(int type){
	if(look_match(0, TokenType::TT_COLON)) return block(type);
	return statement();
}

Statement* Parser::statement(){
	if(match(TokenType::TT_PRINT)) 		return new PrintStatement(expression());
	if(match(TokenType::TT_PUT)) 			return new PutStatement(expression());
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
	if (look_match(0, TokenType::TT_WORD) && look_match(1,TokenType::TT_LPAREN)) {
		return new ExprStatement(function_chain(qualified_name()));
	}

	return assignment_statement();
}

Statement* Parser::assignment_statement(){
	Expression *expr = expression();

	if(dynamic_cast<Statement*>(expr)){
		return dynamic_cast<Statement*>(expr);
	}

	error_pars("Unknown statement " + get(-1).get_text(), get(-1));
	return NULL;
}

Statement* Parser::if_else(){

	Expression* condition = expression();
	Statement* if_statement = statement_or_block(2);
	Statement* else_statemen;

	if(match(TokenType::TT_ELSE) || (
		dynamic_cast<BlockStatement*>(if_statement) &&
		get(-1).get_type() == TokenType::TT_ELSE)
	){
		else_statemen = statement_or_block(1);
	} else {
		else_statemen = NULL;
	}

	return new IfStatement(condition, if_statement, else_statemen);
}

Statement* Parser::while_statement(){
	Expression* condition = expression();
	Statement* statement = statement_or_block(1);
	return new WhileStatement(condition, statement);
}

Statement* Parser::do_while_statement(){
	Statement* statement = statement_or_block(1);
	consume(TokenType::TT_WHILE);
	Expression* condition = expression();
	return new DoWhileStatement(condition, statement);
}

Statement* Parser::for_statement(){

	int foreach_index = look_match(0, TokenType::TT_LPAREN) ? 1 : 0; // не обязательные скобки

	if(look_match(foreach_index, TokenType::TT_WORD)
		&& look_match(foreach_index+1, TokenType::TT_IN)){
		return foreach_arr_statement(false);
	}

	if(look_match(foreach_index, TokenType::TT_WORD)
		&& look_match(foreach_index+1, TokenType::TT_COMMA)
		&& look_match(foreach_index+2, TokenType::TT_WORD)
		&& look_match(foreach_index+3, TokenType::TT_IN)){
		return foreach_arr_statement(true);
	}

	bool open_parent = match(TokenType::TT_LPAREN); // не обязательные скобки

	Statement* initialization = assignment_statement();
	consume(TokenType::TT_COMMA);
	Expression* termintion = expression();
	consume(TokenType::TT_COMMA);
	Statement* incement = assignment_statement();

	if(open_parent) consume(TokenType::TT_RPAREN); 

	Statement* statement = statement_or_block(1);

	return new ForStatement(initialization, termintion, incement, statement);
}

ForeachStatement* Parser::foreach_arr_statement(bool two_vars = false){

	bool open_parent = match(TokenType::TT_LPAREN); // не обязательные скобки

	std::string key = "";
	std::string val = "";

	if(two_vars){
		key = consume(TokenType::TT_WORD).get_text();
		consume(TokenType::TT_COMMA);
		val = consume(TokenType::TT_WORD).get_text();
	} else {
		val = consume(TokenType::TT_WORD).get_text();
	}

	consume(TokenType::TT_IN);
	Expression* container = expression();

	if(open_parent) consume(TokenType::TT_RPAREN); 

	Statement* body = statement_or_block(1);

	return new ForeachStatement(key, val, container, body);
}

FunctionDefineStatement* Parser::function_define(bool is_constexpr){
	// def name(arg1, arg2 = val): ... end || def name(args) = expr
	std::string name = consume(TokenType::TT_WORD).get_text();
	Arguments args = arguments();
	Statement* body = statement_body();
	return new FunctionDefineStatement(name, args, body, is_constexpr);
}

Arguments Parser::arguments(){
	// (arg1, arg2, arg3 = expr1)
	Arguments arguments;
	bool start_optional_args = false;
	consume(TokenType::TT_LPAREN);
	while(!match(TT_RPAREN)){
		std::string name = consume(TokenType::TT_WORD).get_text();
		if(match(TokenType::TT_EQ)){
			start_optional_args = true;
			arguments.add_optional(name, variable(false));
		} else if (!start_optional_args){
			arguments.add_required(name);
		} else {
			error_pars("Required argument cannot be after optional", get(0));
		}
		match(TokenType::TT_COMMA);
	}
	return arguments;
}

Statement* Parser::statement_body(){
	if(match(TokenType::TT_EQ))
		return new ReturnStatement(expression());
	return statement_or_block(1);
}

Expression* Parser::function_chain(Expression *qualified_name_expr){
	// f1()()() || f1().f2().f3() || f1().key

	Expression* expr = function(qualified_name_expr);
	
	if(look_match(0, TokenType::TT_LPAREN)){
		return function_chain(expr);
	}

	if(look_match(0, TokenType::TT_DOT)){
		std::vector<Expression* > indices = variable_suffix();
		if(indices.empty()) return expr;

		if(look_match(0, TokenType::TT_LPAREN)){
			// next function call
			return function_chain(new ContainerAccessExpression(expr, indices));
		}
		// container access	
		return new ContainerAccessExpression(expr, indices);
	}

	return expr; 
}

FunctionalExpression* Parser::function(Expression *qualified_name_expr){
	// function(arg1, arg2, ...)

	consume(TokenType::TT_LPAREN);
	FunctionalExpression* function = new FunctionalExpression(qualified_name_expr);
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

Expression* Parser::map_vals(){
	// {key1: value1, key2: value2, ...}
	consume(TokenType::TT_LBRACE);
	std::map<Expression*, Expression*> elements;
	while(!match(TokenType::TT_RBRACE)){
		
		Expression* key = expression();

		if(elements.find(key) != elements.end())
			error_pars("Key '" + key->to_s() + "' already exists", get(0));
		
		consume(TokenType::TT_COLON);
		Expression* val = expression();

		elements[key] = val;
		match(TokenType::TT_COMMA);
	}

	return new MapExpression(elements);
}

Expression* Parser::expression(){
	return assignment();
}

Expression* Parser::assignment(){
	Expression* assignment = assignment_strict();

	if(assignment != NULL){
		return assignment;
	}

	return ternary();
}

Expression* Parser::assignment_strict(){
	int position = this->pos;
	Expression* target_expr = qualified_name();
	
	if((target_expr == NULL) || !(dynamic_cast<Accessible*>(target_expr))){
		this->pos = position;
		return NULL;
	}
	TokenType current_type = get(0).get_type();
	if(NS_Parser::ASSIGN_OPERATORS.find(current_type) == NS_Parser::ASSIGN_OPERATORS.end()){
		this->pos = position;
		return NULL;
	}
	
	match(current_type);

	NS_Binary::Operator op = NS_Parser::ASSIGN_OPERATORS[current_type];
	
	Expression* expr;

	if(match(TokenType::TT_INPUT)){
		expr = dynamic_cast<Expression*>(new InputExpression());
	} else {
		expr = expression();
	}

	return new AssignmentExpression(op, dynamic_cast<Accessible*>(target_expr), expr);
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
			expression = new BinaryExpression(NS_Binary::Operator::OR, expression, bitwiseXor());
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
			expression = new BinaryExpression(NS_Binary::Operator::XOR, expression, bitwiseAnd());
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
			expression = new BinaryExpression(NS_Binary::Operator::AND, expression, equality());
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
			// expression = new BinaryExpression(NS_Binary::Operator::LSHIFT, expression, additive());
			expression = new BinaryExpression(NS_Binary::Operator::LSHIFT, expression, additive());
			continue;
		}
		if (match(TokenType::TT_GTGT)) {
			expression = new BinaryExpression(NS_Binary::Operator::RSHIFT, expression, additive());
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::additive(){
	Expression *result = multiplicative();

	while (true) {
		if (match(TokenType::TT_PLUS)) {
				result = new BinaryExpression(NS_Binary::Operator::ADD, result, multiplicative());
				continue;
		}
		if (match(TokenType::TT_MINUS)) {
			result = new BinaryExpression(NS_Binary::Operator::SUBTRACT, result, multiplicative());
			continue;
		}
		break;
	}
	
	return result;
}

Expression* Parser::multiplicative(){
	Expression *result = unary();

	while (true) {
		if (match(TokenType::TT_STAR)) {
			result = new BinaryExpression(NS_Binary::Operator::MULTIPLY, result, unary());
			continue;
		}
		if (match(TokenType::TT_SLASH)) {
			result = new BinaryExpression(NS_Binary::Operator::DIVIDE, result, unary());
			continue;
		}
		if (match(TokenType::TT_PERCENT)) {
			result = new BinaryExpression(NS_Binary::Operator::REMAINDER, result, unary());
			continue;
		}
		// if (match(TokenType::TT_STARSTAR)) {
		// 	result = new BinaryExpression(NS_Binary::Operator::POWER, result, unary());
		// 	continue;
		// }
		break;
	}

	return result;
}

Expression* Parser::unary(){
	
	if (match(TokenType::TT_PLUSPLUS)) {
		return new UnaryExpression(
			NS_Unary::Operator::INCREMENT_PREFIX, primary(true)
		);
	}
	if (match(TokenType::TT_MINUSMINUS)) {
		return new UnaryExpression(
			NS_Unary::Operator::DECREMENT_PREFIX, primary(true)
		);
	}

	if(match(TokenType::TT_MINUS)) {
		return new UnaryExpression(NS_Unary::Operator::NEGATE, primary(false));
	}
	if (match(TokenType::TT_EXCL)) {
		return new UnaryExpression(NS_Unary::Operator::NOT, primary(false));
	}
	if (match(TokenType::TT_TILDE)) {
		return new UnaryExpression(NS_Unary::Operator::COMPLEMENT, primary(false));
	}
	if(match(TokenType::TT_PLUS)){
		return primary(false);
	}

	return primary(false);
}

Expression* Parser::primary(bool incr = false) {

	if(match(TokenType::TT_LPAREN)){
		Expression* result = expression();
		consume(TokenType::TT_RPAREN);
		return result;
	}

	if(match(TokenType::TT_DEF)){
		Arguments args = arguments();
		Statement* statement = statement_body();
		return new ValueExpression(new UserDefineFunction(args, statement));
	}

	return variable(incr);
}

Expression* Parser::variable(bool incr = false) {

	if(look_match(0,TokenType::TT_WORD) && look_match(1, TokenType::TT_LPAREN)){
		return function_chain(new ValueExpression(consume(TokenType::TT_WORD).get_text()));
	}

	Expression* qualified_name_expr = qualified_name();
	if(qualified_name_expr != NULL){
		// variable(args) || arr["key"](args) || obj.key(args)
		if(look_match(0, TokenType::TT_LPAREN)){
			return function_chain(qualified_name_expr);
		}
		if(!incr){
			// postfix increment/decrement
			if(match(TokenType::TT_PLUSPLUS)){
				return new UnaryExpression(
					NS_Unary::Operator::INCREMENT_POSTFIX, qualified_name_expr
				);
			}
			if(match(TokenType::TT_MINUSMINUS)){
				return new UnaryExpression(
					NS_Unary::Operator::DECREMENT_POSTFIX, qualified_name_expr
				);
			}
		}
		return qualified_name_expr;
	}

	if(look_match(0,TokenType::TT_LBRACKET)){
		return array();
	}

	if(look_match(0,TokenType::TT_LBRACE)){
		return map_vals();
	}

	return value();
}

Expression* Parser::qualified_name(){
	// var || var.key[index].key2
	Token current = get(0);
	if(!match(TokenType::TT_WORD))
		return NULL;

	std::vector<Expression*> indices = variable_suffix();
	if(indices.empty()){
		return new VariableExpression(current.get_text());
	}
	return new ContainerAccessExpression(current.get_text(), indices);
}

std::vector<Expression*> Parser::variable_suffix(){
	// .key1.arr1[expr1][expr2].key2
	if(!look_match(0, TokenType::TT_DOT) && !look_match(0, TokenType::TT_LBRACKET)){
		return {};
	}
	std::vector<Expression*> indices;
	while(look_match(0, TokenType::TT_DOT) || look_match(0, TokenType::TT_LBRACKET)){
		if(match(TokenType::TT_DOT)){
			std::string field_name = consume(TokenType::TT_WORD).get_text();
			Expression* key = new ValueExpression(field_name);
			indices.push_back(key);
		}
		if(match(TokenType::TT_LBRACKET)){
			indices.push_back(expression());
			consume(TokenType::TT_RBRACKET);
		}
	}
	return indices;
}

Expression* Parser::value() {

	Token current = this->get(0);

	if(match(TokenType::TT_NUMBER)){
		std::string the_num = current.get_text();
		if(func::find_c(the_num, '.')){
			return new ValueExpression(atof(&current.get_text()[0u]));
		}else{
			try{
				int num = std::stoi(the_num);
				return new ValueExpression(num);
			} catch (std::exception& e){
				try{
					long num = std::atol(&the_num[0u]);
					return new ValueExpression(num);
				} catch (std::exception& e){
					error_pars("Very big number", current);
				}
			}
		}
	}

	if(match(TokenType::TT_HEX_NUMBER)){
		return new ValueExpression((double)std::stol(&current.get_text()[0u], 0, 16));
	}
	if(match(TokenType::TT_OCTAL_NUMBER)){
		return new ValueExpression((double)std::stol(&current.get_text()[0u], 0, 8));
	}
	if(match(TokenType::TT_BINARY_NUMBER)){
		return new ValueExpression((double)std::stol(&current.get_text()[0u], 0, 2));
	}
	if(match(TokenType::TT_TEXT)){
		return new ValueExpression(current.get_text());
	}

	error_pars("Unknown expression: " + current.get_text(), current);
	exit(1);
}

Token Parser::consume(TokenType type){

	Token current = get(0);

	if(type != current.get_type()){
		error_pars("Token " + TokenToString(current.get_type()) +
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

bool Parser::match_or_match(std::vector<TokenType> types){

	Token current = get(0);

	bool res = false;
	for(auto type: types){
		if(type == current.get_type()){
			res = true;
			break;
		}
	}

	if(res) pos++;
	return res;
}

bool Parser::look_match(int pos, TokenType type) {
	return get(pos).get_type() == type;
}

Token Parser::get(int rel_pos){
	int position = pos + rel_pos;
	if(position >= size) return TT_EOF_T;
	return tokens[position];
}

bool Parser::end_the_block(int type){
	if(type == 2)
		return end_block_if();
	// else if(type == 3)
		// return end_block_else_if();
	
	return end_block();
}

bool Parser::end_block(){
	return !match(TokenType::TT_END);
}

bool Parser::end_block_if(){
	return (!match_or_match({TokenType::TT_END, TokenType::TT_ELSE}));
}

bool Parser::end_block_else_if(){
	// return (!match_or_match(TokenType::TT_END, TokenType::TT_ELIF));
	return false;
}

void Parser::error_pars(std::string text, Token t){
	
	if(t.get_row() == -1 || t.get_col() == -1){
		t = get(-1);
	}

	// std::string expr_err = t.to_s();

	std::cout << "Parser error " << t.get_position() << ": " << text << std::endl; 
	exit(1);
}

#endif
