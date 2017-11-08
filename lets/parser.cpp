//
//  parser.cpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/parser.hpp"
#include "../include/ex_parse.h"

#include "../include/arguments.hpp"

#include "../include/l_user_define_function.hpp"
#include "../include/include_ast.h"

lets_map_t<u_tt_t, NS_Binary::Operator> Parser::ASSIGN_OPERATORS = {
	{ TT_EQ, NS_Binary::Operator::THE_NULL },
	{ TT_PLUSEQ, NS_Binary::Operator::ADD },
	{ TT_MINUSEQ, NS_Binary::Operator::SUBTRACT },
	{ TT_STAREQ, NS_Binary::Operator::MULTIPLY },
	{ TT_SLASHEQ, NS_Binary::Operator::DIVIDE },
	{ TT_PERCENTEQ, NS_Binary::Operator::REMAINDER },
	{ TT_AMPEQ, NS_Binary::Operator::AND },
	{ TT_CARETEQ, NS_Binary::Operator::XOR },
	{ TT_BAREQ, NS_Binary::Operator::OR },
	{ TT_LTLT, NS_Binary::Operator::LSHIFT },
	{ TT_GTGT, NS_Binary::Operator::RSHIFT },
	// {TT_ATEQ, NS_Binary::Operator::AT}
};

Parser::Parser(){}

Parser::Parser(lets_vector_t<Token> tokens) :tokens(std::move(tokens)), pos(0) {
	size = (int)this->tokens.size();
}

BlockStatement* Parser::parse(){
	BlockStatement* result = new BlockStatement();
	while(!match(TT_EOF)){
		try{
			result->add(statement());
		} catch (ParseException& pe){
			throw pe;
		}
	}
	
	return result;
}

Statement* Parser::get_parsed_statement(){
	return this->parsed_statement;
}

Statement* Parser::block(){
	BlockStatement* block = new BlockStatement();
	
	consume(TT_COLON);
	while(!match(TT_KW_END)){
		block->add(statement());
	}
	
	return block;
}

Statement* Parser::statement_or_block(){
	if(look_match(0, TT_COLON)) return block();
	return statement();
}

Statement* Parser::block(u_tt_t end_kw_block){
	BlockStatement* block = new BlockStatement();
	
	consume(TT_COLON);
	while(!match(end_kw_block)){
		block->add(statement());
	}
	
	return block;
}

Statement* Parser::statement_or_block(u_tt_t end_kw_block){
	if(look_match(0, TT_COLON)) return block(end_kw_block);
	return statement();
}

Statement* Parser::statement(){
	if(match(TT_KW_PRINT))      return new PrintStatement(expression());
	if(match(TT_KW_PUT))        return new PutStatement(expression());
	if(match(TT_KW_IF))         return if_else();
	if(match(TT_KW_DO))         return do_while_statement();
	if(match(TT_KW_WHILE))      return while_statement();
	if(match(TT_KW_BREAK))      return new BreakStatement();
	if(match(TT_KW_CONTINUE))   return new ContinueStatement();
	if(match(TT_KW_RETURN))     return new ReturnStatement(expression());
	// if(match(TT_KW_SELF))    return new SelfStatement(arguments());
	if(match(TT_KW_USE))        return use_statement();
	if(match(TT_KW_FOR))        return for_statement();
	if(match(TT_KW_DEF))        return function_define(false);
	if(match(TT_KW_DEF_C))      return function_define(true);
	//    if(match(TT_KW_MODE))         return new ModeProgrammStatement(expression()->eval()->as_string());
	if(match(TT_KW_MATCH))      return match();
	if (look_match(0, TT_IDENTIFIER) && look_match(1,TT_LPAREN)) {
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
	Statement* if_statement;
	Statement* else_statement;
	
	if(match(TT_COLON)){
		BlockStatement* block = new BlockStatement();
		while(true){
			if(match(TT_KW_END)){
				else_statement = NULL;
				break;
			}
			if(match(TT_COLON) && match(TT_KW_ELSE)){
				else_statement = statement_or_block();
				break;
			}
			block->add(statement());
		}
		if_statement = block;
	} else {
		if_statement = statement();
		if(match(TT_KW_ELSE)){
			else_statement = statement_or_block();
		} else {
			else_statement = NULL;
		}
	}
	
	return new IfStatement(condition, if_statement, else_statement);
}

Statement* Parser::while_statement(){
	Expression* condition = expression();
	Statement* statement = statement_or_block();
	return new WhileStatement(condition, statement);
}

Statement* Parser::do_while_statement(){
	Statement* statement = statement_or_block(TT_KW_WHILE);
	Expression* condition = expression();
	return new DoWhileStatement(condition, statement);
}

Statement* Parser::for_statement(){
	
	int foreach_index = look_match(0, TT_LPAREN) ? 1 : 0; // не обязательные скобки
	
	if(look_match(foreach_index, TT_IDENTIFIER)
	   && look_match(foreach_index+1, TT_KW_IN)){
		return foreach_arr_statement(false);
	}
	
	if(look_match(foreach_index, TT_IDENTIFIER)
	   && look_match(foreach_index+1, TT_COMMA)
	   && look_match(foreach_index+2, TT_IDENTIFIER)
	   && look_match(foreach_index+3, TT_KW_IN)){
		return foreach_arr_statement(true);
	}
	
	bool open_parent = match(TT_LPAREN); // не обязательные скобки
	
	Statement* initialization = assignment_statement();
	consume(TT_COMMA);
	Expression* termintion = expression();
	consume(TT_COMMA);
	Statement* incement = assignment_statement();
	
	if(open_parent) consume(TT_RPAREN);
	
	Statement* statement = statement_or_block();
	
	return new ForStatement(initialization, termintion, incement, statement);
}

Statement* Parser::use_statement(){
	if(look_match(0, TT_LBRACKET)){
		Expression *elements = array();
		consume(TT_KW_IN);
		return new UseStatement(expression(), elements);
	} else {
		return new UseStatement(expression());
	}
}

ForeachStatement* Parser::foreach_arr_statement(bool two_vars = false){
	
	bool open_parent = match(TT_LPAREN); // не обязательные скобки
	
	lets_str_t key = "";
	lets_str_t val = "";
	
	if(two_vars){
		key = consume(TT_IDENTIFIER).get_text();
		consume(TT_COMMA);
		val = consume(TT_IDENTIFIER).get_text();
	} else {
		val = consume(TT_IDENTIFIER).get_text();
	}
	
	consume(TT_KW_IN);
	Expression* container = expression();
	
	if(open_parent) consume(TT_RPAREN);
	
	Statement* body = statement_or_block();
	
	return new ForeachStatement(key, val, container, body);
}

FunctionDefineStatement* Parser::function_define(bool is_constexpr){
	// def name(arg1, arg2 = val): ... end || def name(args) = expr
	lets_str_t name = consume(TT_IDENTIFIER).get_text();
	Arguments args = arguments();
	Statement* body = statement_body();
	return new FunctionDefineStatement(name, args, body, is_constexpr);
}

Arguments Parser::arguments(){
	// (arg1, arg2, arg3 = expr1)
	Arguments arguments;
	bool start_optional_args = false;
	consume(TT_LPAREN);
	while(!match(TT_RPAREN)){
		lets_str_t name = consume(TT_IDENTIFIER).get_text();
		if(match(TT_EQ)){
			start_optional_args = true;
			arguments.add_optional(name, variable(false));
		} else if (!start_optional_args){
			arguments.add_required(name);
		} else {
			error_pars("Required argument cannot be after optional", get(0));
		}
		match(TT_COMMA);
	}
	return arguments;
}

Statement* Parser::statement_body(){
	if(match(TT_LTMINUS))
		return new ReturnStatement(expression());
	
	return statement_or_block();
}

Expression* Parser::function_chain(Expression *qualified_name_expr){
	// f1()()() || f1().f2().f3() || f1().key
	
	Expression* expr = function(qualified_name_expr);
	
	if(look_match(0, TT_LPAREN)){
		return function_chain(expr);
	}
	
	if(look_match(0, TT_DOT)){
		lets_vector_t<Expression* > indices = variable_suffix();
		if(indices.empty()) return expr;
		
		if(look_match(0, TT_LPAREN)){
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
	
	consume(TT_LPAREN);
	FunctionalExpression* function = new FunctionalExpression(qualified_name_expr);
	
	while(!match(TT_RPAREN)){
		function->add_arguments(expression());
		match(TT_COMMA);
	}
	
	
	return function;
}

Expression* Parser::array(){
	consume(TT_LBRACKET);
	
	lets_vector_t<Expression* > elements;
	
	while(!match(TT_RBRACKET)){
		elements.push_back(expression());
		match(TT_COMMA);
	}
	
	return new ArrayExpression(elements);
}

Expression* Parser::map_vals(){
	// {key1: value1, key2: value2, ...}
	consume(TT_LBRACE);
	lets_map_t<Expression*, Expression*> elements;
	while(!match(TT_RBRACE)){
		
		Expression* key = expression();
		
		if(elements.find(key) != elements.end())
			error_pars("Key '" + key->to_s() + "' already exists", get(0));
		
		consume(TT_COLON);
		Expression* val = expression();
		
		elements[key] = val;
		match(TT_COMMA);
	}
	
	return new MapExpression(elements);
}

MatchExpression* Parser::match(){
	// match expression :
	//  case pattern1: result1
	//  case pattern2 if extr: result2
	// end
	
	return NULL;
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
	int current_type = get(0).get_type();
	if(ASSIGN_OPERATORS.find(current_type) == ASSIGN_OPERATORS.end()){
		this->pos = position;
		return NULL;
	}
	
	match(current_type);
	
	NS_Binary::Operator op = ASSIGN_OPERATORS[current_type];
	
	return new AssignmentExpression(op, dynamic_cast<Accessible*>(target_expr), expression());
}

Expression* Parser::ternary() {
	Expression* result = logicalOr();
	
	if (match(TT_QUESTION)) {
		Expression* trueExpr = expression();
		consume(TT_COLON);
		Expression* falseExpr = expression();
		return new TernaryExpression(result, trueExpr, falseExpr);
	}
	
	return result;
}

Expression* Parser::logicalOr(){
	Expression* result = logicalAnd();
	while(true){
		if(match(TT_BARBAR)){
			result = new ConditionalExpression(NS_Conditional::Operator::OR, result, logicalAnd());
			continue;
		}
		break;
	}
	return result;
}

Expression* Parser::logicalAnd(){
	Expression* result = bitwiseOr();
	while(true){
		if(match(TT_AMPAMP)){
			result = new ConditionalExpression(NS_Conditional::Operator::AND, result, bitwiseOr());
			continue;
		}
		break;
	}
	return result;
}

Expression* Parser::bitwiseOr() {
	
	Expression* expression = bitwiseXor();
	
	while (true) {
		if (match(TT_BAR)) {
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
		if (match(TT_CARET)) {
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
		if (match(TT_AMP)) {
			expression = new BinaryExpression(NS_Binary::Operator::AND, expression, equality());
			continue;
		}
		break;
	}
	
	return expression;
}

Expression* Parser::equality(){
	Expression* result = conditional();
	
	if(match(TT_EQEQ)){
		return new ConditionalExpression(NS_Conditional::Operator::EQUALS, result, conditional());
	}
	if(match(TT_EXCLEQ)){
		return new ConditionalExpression(NS_Conditional::Operator::NOT_EQUALS, result, conditional());
	}
	
	return result;
}

Expression* Parser::conditional(){
	Expression* result = shift();
	
	while(true){
		if(match(TT_LT)){
			result = new ConditionalExpression(NS_Conditional::Operator::LT, result, shift());
			continue;
		}
		if(match(TT_LTEQ)){
			result = new ConditionalExpression(NS_Conditional::Operator::LTEQ, result, shift());
			continue;
		}
		if(match(TT_GT)){
			result = new ConditionalExpression(NS_Conditional::Operator::GT, result, shift());
			continue;
		}
		if(match(TT_GTEQ)){
			result = new ConditionalExpression(NS_Conditional::Operator::GTEQ, result, shift());
			continue;
		}
		break;
	}
	
	return result;
}

Expression* Parser::shift() {
	Expression *expression = additive();
	
	while (true) {
		if (match(TT_LTLT)) {
			// expression = new BinaryExpression(NS_Binary::Operator::LSHIFT, expression, additive());
			expression = new BinaryExpression(NS_Binary::Operator::LSHIFT, expression, additive());
			continue;
		}
		if (match(TT_GTGT)) {
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
		if (match(TT_PLUS)) {
			result = new BinaryExpression(NS_Binary::Operator::ADD, result, multiplicative());
			continue;
		}
		if (match(TT_MINUS)) {
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
		if (match(TT_STAR)) {
			result = new BinaryExpression(NS_Binary::Operator::MULTIPLY, result, unary());
			continue;
		}
		if (match(TT_SLASH)) {
			result = new BinaryExpression(NS_Binary::Operator::DIVIDE, result, unary());
			continue;
		}
		if (match(TT_PERCENT)) {
			result = new BinaryExpression(NS_Binary::Operator::REMAINDER, result, unary());
			continue;
		}
		// if (match(TT_STARSTAR)) {
		//  result = new BinaryExpression(NS_Binary::Operator::POWER, result, unary());
		//  continue;
		// }
		break;
	}
	
	return result;
}

Expression* Parser::unary(){
	
	if (match(TT_PLUSPLUS)) {
		return new UnaryExpression(
								   NS_Unary::Operator::INCREMENT_PREFIX, primary(true)
								   );
	}
	if (match(TT_MINUSMINUS)) {
		return new UnaryExpression(
								   NS_Unary::Operator::DECREMENT_PREFIX, primary(true)
								   );
	}
	
	if(match(TT_MINUS)) {
		return new UnaryExpression(NS_Unary::Operator::NEGATE, primary(false));
	}
	if (match(TT_EXCL)) {
		return new UnaryExpression(NS_Unary::Operator::NOT, primary(false));
	}
	if (match(TT_TILDE)) {
		return new UnaryExpression(NS_Unary::Operator::COMPLEMENT, primary(false));
	}
	if(match(TT_PLUS)){
		return primary(false);
	}
	
	return primary(false);
}

Expression* Parser::primary(bool incr = false) {
	
	if(match(TT_LPAREN)){
		Expression* result = expression();
		consume(TT_RPAREN);
		return result;
	}
	
	if(match(TT_KW_DEF)){
		Arguments args = arguments();
		Statement* statement = statement_body();
		return new ValueExpression(new UserDefineFunction(args, statement));
	}
	
	return variable(incr);
}

Expression* Parser::variable(bool incr = false) {
	
	if(look_match(0,TT_IDENTIFIER) && look_match(1, TT_LPAREN)){
		return function_chain(new ValueExpression(consume(TT_IDENTIFIER).get_text()));
	}
	
	Expression* qualified_name_expr = qualified_name();
	if(qualified_name_expr != NULL){
		// variable(args) || arr["key"](args) || obj.key(args)
		if(look_match(0, TT_LPAREN)){
			return function_chain(qualified_name_expr);
		}
		if(!incr){
			// postfix increment/decrement
			if(match(TT_PLUSPLUS)){
				return new UnaryExpression(NS_Unary::Operator::INCREMENT_POSTFIX, qualified_name_expr);
			}
			if(match(TT_MINUSMINUS)){
				return new UnaryExpression(NS_Unary::Operator::DECREMENT_POSTFIX, qualified_name_expr);
			}
		}
		return qualified_name_expr;
	}
	
	if(look_match(0,TT_LBRACKET)){
		return array();
	}
	
	if(look_match(0,TT_LBRACE)){
		return map_vals();
	}
	
	return value();
}

Expression* Parser::qualified_name(){
	// var || var.key[index].key2
	Token current = get(0);
	if(!match(TT_IDENTIFIER))
		return NULL;
	
	lets_vector_t<Expression*> indices = variable_suffix();
	if(indices.empty()){
		return new VariableExpression(current.get_text());
	}
	return new ContainerAccessExpression(current.get_text(), indices);
}

lets_vector_t<Expression*> Parser::variable_suffix(){
	// .key1.arr1[expr1][expr2].key2
	if(!look_match(0, TT_DOT) && !look_match(0, TT_LBRACKET)){
		return {};
	}
	lets_vector_t<Expression*> indices;
	while(look_match(0, TT_DOT) || look_match(0, TT_LBRACKET)){
		if(match(TT_DOT)){
			lets_str_t field_name = consume(TT_IDENTIFIER).get_text();
			Expression* key = new ValueExpression(field_name);
			indices.push_back(key);
		}
		if(match(TT_LBRACKET)){
			indices.push_back(expression());
			consume(TT_RBRACKET);
		}
	}
	return indices;
}

Expression* Parser::value() {
	
	Token current = this->get(0);
	
	if(match(TT_NUMBER)){
		lets_str_t the_num = current.get_text();
		if(the_num.find('.') != lets_str_t::npos){
			return new ValueExpression(atof(&current.get_text()[0u]));
		}else{
			try{
				int num = std::stoi(the_num);
				return new ValueExpression(num);
			} catch (std::exception& e){
				try{
					the_num = the_num.substr(0, 19);
					long num = std::atol(&the_num[0u]);
					dbg(num)
					return new ValueExpression(num);
				} catch (std::exception& e){
					error_pars("Very big number", current);
				}
			}
		}
	}
	
	if(match(TT_HEX_NUMBER)){
		return new ValueExpression((double)std::stol(&current.get_text()[0u], 0, 16));
	}
	if(match(TT_OCTAL_NUMBER)){
		return new ValueExpression((double)std::stol(&current.get_text()[0u], 0, 8));
	}
	if(match(TT_BINARY_NUMBER)){
		return new ValueExpression((double)std::stol(&current.get_text()[0u], 0, 2));
	}
	if(match(TT_STRING)){
		return new ValueExpression(current.get_text());
	}
	
	// dbg(get(-1).to_s());
	error_pars("Unknown expression: " + current.get_text(), current);
	//    if(!Mode_Programm::without_stop){
	exit(1);
	//    }
	return NULL;
}

Token Parser::consume(u_tt_t type){
	
	Token current = get(0);
	
	if(type != current.get_type()){
		error_pars("Token " + TokenTypeString[current.get_type()] + " dosn't match " + TokenTypeString[type], current);
	}
	
	pos++;
	return current;
}

bool Parser::match(u_tt_t type){
	
	Token current = get(0);
	if(type != current.get_type()) return false;
	pos++;
	
	return true;
}

bool Parser::match(lets_vector_t<u_tt_t> types){
	
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

bool Parser::look_match(int pos, u_tt_t type) {
	return get(pos).get_type() == type;
}

Token Parser::get(u_tt_t rel_pos){
	int position = pos + rel_pos;
	if(position >= size) return TT_EOF_T;
	return tokens[position];
}

int Parser::find_c(lets_str_t s, char c) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == c) {
			return i;
		}
	}
	return -1;
}

void Parser::error_pars(lets_str_t text, Token t){
	
	if(t.get_row() == -1 || t.get_col() == -1){
		t = get(-1);
	}
	
	// lets_str_t expr_err = t.to_s();
	
	lets_output("Parser error " << t.get_position() << ": " << text)
	exit(1);
	
	//    if(!Mode_Programm::without_stop){
	//    }
}