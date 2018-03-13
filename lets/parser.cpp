//
//  parser.cpp
//  lets
//
//  Created by Dragan Stepan on 02.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/parser.hpp"
#include "../include/operator.hpp"
#include "../include/keyword.hpp"
#include "../include/lets.hpp"
#include "../include/exception/parse.h"

#include "../include/arguments.hpp"

#include "../include/lib/user_define_function.hpp"
#include "../include/lib/string_value.hpp"
#include "../include/lib/number.hpp"
#include "../include/include_ast.h"
#include "../include/tools.hpp"

#define GET_ROW(i) get(i).get_row()
#define GET_COL(i) get(i).get_col()

#define consume_op(OP) consume_operator(GET_OP(OP))
#define match_op(OP) match_operator(GET_OP(OP))
#define look_match_op(I, OP) look_match_operator(I, GET_OP(OP))

#define CONSUME_KW(KW) consume_keyword(GET_KW(KW))
#define MATCH_KW(KW) match_keyword(GET_KW(KW))
#define LOOK_MATCH_KW(I, KW) look_match_keyword(I, GET_KW(KW))

#define NEW_STATEMENT_RETURN(NAME, ROW, COL) { \
	NAME##Statement* NAME##__s = new NAME##Statement(); \
	NAME##__s->set_position(ROW, COL); \
	return NAME##__s; \
};

#define NEW_STATEMENT_RETURN_ARG(NAME, ROW, COL, ARG) { \
	size_t r = ROW;\
	size_t c = COL;\
	NAME##Statement* NAME##__s = new NAME##Statement ARG; \
	NAME##__s->set_position(r, c); \
	return NAME##__s; \
};

#define NEW_STATEMENT_EQUAL_ARG(TO_EQ, NAME, ROW, COL, ARG) { \
	size_t r = ROW;\
	size_t c = COL;\
	NAME##Statement* NAME##__s = new NAME##Statement ARG; \
	NAME##__s->set_position(r, c); \
	TO_EQ = NAME##__s; \
};

#define NEW_EXPRESSION_RETURN(NAME, ROW, COL) { \
	NAME##Expression* NAME##__expr_temp = new NAME##Expression(); \
	NAME##__expr_temp->set_position(ROW, COL); \
	return NAME##__expr_temp; \
};

#define NEW_EXPRESSION_RETURN_ARG(NAME, ROW, COL, ARG) { \
	size_t r = ROW;\
	size_t c = COL;\
	NAME##Expression* NAME##__s = new NAME##Expression ARG; \
	NAME##__s->set_position(r, c); \
	return NAME##__s; \
};

#define NEW_EXPRESSION_EQUAL_ARG(TO_EQ, NAME, ROW, COL, ARG) { \
	size_t r = ROW;\
	size_t c = COL;\
	NAME##Expression* NAME##__s = new NAME##Expression ARG; \
	NAME##__s->set_position(r, c); \
	TO_EQ = NAME##__s; \
};


lets_map_t<u_tt_t, NS_Binary::Operator> Parser::ASSIGN_OPERATORS = {
	{GET_OP(EQ), NS_Binary::Operator::THE_NULL},
	{GET_OP(PLUSEQ), NS_Binary::Operator::ADD},
	{GET_OP(MINUSEQ), NS_Binary::Operator::SUBTRACT},
	{GET_OP(STAREQ), NS_Binary::Operator::MULTIPLY},
	{GET_OP(SLASHEQ), NS_Binary::Operator::DIVIDE},
	{GET_OP(PERCENTEQ), NS_Binary::Operator::REMAINDER},
	{GET_OP(AMPEQ), NS_Binary::Operator::AND},
	{GET_OP(CARETEQ), NS_Binary::Operator::XOR},
	{GET_OP(BAREQ), NS_Binary::Operator::OR},
	{GET_OP(LTLT), NS_Binary::Operator::LSHIFT},
	{GET_OP(GTGT), NS_Binary::Operator::RSHIFT},
};

// Parser::Parser(){}

Parser::Parser(lets_vector_t<Token> t) : tokens(std::move(t)), pos(0) {
	this->size = this->tokens.size();
	if(this->tokens.size() > 0){
		TT_EOF_T.set_row(this->tokens.back().get_row());
		TT_EOF_T.set_col(this->tokens.back().get_col());
	}
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

// Statement* Parser::get_parsed_statement(){
	// return this->parsed_statement;
// }

Statement* Parser::block(){
	BlockStatement* block = new BlockStatement();

	consume_op(COLON);
	while(!MATCH_KW(END)){
		block->add(statement());
	}

	return block;
}

Statement* Parser::block(u_tt_t kw_end_block){
	BlockStatement* block = new BlockStatement();

	consume_op(COLON);
	while(!match_keyword(kw_end_block)){
		block->add(statement());
	}

	return block;
}

Statement* Parser::block(lets_vector_t<u_tt_t> kws_end_block){
	BlockStatement* block = new BlockStatement();

	consume_op(COLON);
	while(!this->match_keywords(kws_end_block)){
		block->add(statement());
	}

	return block;
}

Statement* Parser::statement_or_block(){
	if(look_match_op(0, COLON)) return block();
	return statement();
}

Statement* Parser::statement_or_block(u_tt_t kw_end_block){
	if(look_match_op(0, COLON)) return block(kw_end_block);
	return statement();
}

Statement* Parser::statement(){
	if(MATCH_KW(PRINT))      NEW_STATEMENT_RETURN_ARG(Print, GET_ROW(-1), GET_COL(-1), (expression()))
	if(MATCH_KW(PUT))        NEW_STATEMENT_RETURN_ARG(Put, GET_ROW(-1), GET_COL(-1), (expression()))
	if(MATCH_KW(IF))         return if_else();
	if(MATCH_KW(DO))         return do_while_statement();
	if(MATCH_KW(WHILE))      return while_statement();
	if(MATCH_KW(BREAK))      NEW_STATEMENT_RETURN(Break, GET_ROW(-1), GET_COL(-1))
	if(MATCH_KW(CONTINUE))   NEW_STATEMENT_RETURN(Continue, GET_ROW(-1), GET_COL(-1))
	if(MATCH_KW(RETURN))     NEW_STATEMENT_RETURN_ARG(Return, GET_ROW(-1), GET_COL(-1), (expression()))
	if(MATCH_KW(USE))        return use_statement();
	if(MATCH_KW(FOR))        return for_statement();
	if(MATCH_KW(DEF))        return function_define();
	// if(MATCH_KW(CLASS))      return class_define();
	if(MATCH_KW(MATCH))      return match();
	if (look_match(0, TT_IDENTIFIER) && look_match_op(1, LPAREN)) {
		NEW_STATEMENT_RETURN_ARG(Expr, GET_ROW(0), GET_COL(0), (function_chain((qualified_name()))))
	}
	if (look_match_op(0, BACKSLASH)) {
		return multi_assignment_statement();
	}

	return assignment_statement();
}

Statement* Parser::assignment_statement(){
	Expression *expr = expression();

	if(dynamic_cast<Statement*>(expr)){
		return dynamic_cast<Statement*>(expr);
	}

	error_pars("Unknown statement " + get(-1).to_s(), get(-1));
	return NULL;
}

Statement* Parser::multi_assignment_statement(){
	size_t row = GET_ROW(0), col = GET_COL(0);
	lets_vector_t<Accessible*> elements;

	consume_op(BACKSLASH);

	while(!match_op(BACKSLASH)){
		Expression* target_expr = this->qualified_name();

		if(target_expr == NULL){
			this->error_pars("Variable expected. Got: " + get(0).to_s(), get(0));
		}
		if(!(dynamic_cast<Accessible*>(target_expr))){
			this->error_pars("Variable expected. Got: " + target_expr->to_s(), target_expr);
		}

		elements.push_back(dynamic_cast<Accessible*>(target_expr));

		match_op(COMMA);
	}

	consume_op(EQ);

	NEW_STATEMENT_RETURN_ARG(MultiAssignment, row, col, (elements, this->expression()))
}

Statement* Parser::if_else(){

	size_t row = GET_ROW(-1), col = GET_COL(-1);

	Expression* condition = expression();
	BlockStatement* if_statement = new BlockStatement();
	BlockStatement* else_statement = NULL;

	while(!this->match_keywords({GET_KW(ELSE), GET_KW(END), GET_KW(ELIF)})){
		if_statement->add(statement());
	}

	if(LOOK_MATCH_KW(-1, ELIF)){
		NEW_STATEMENT_RETURN_ARG(If, row, col, (condition, if_statement, if_else()))
	}

	if(LOOK_MATCH_KW(-1, ELSE)){
		else_statement = new BlockStatement();
		while(!MATCH_KW(END))
			else_statement->add(statement());
	} 

	NEW_STATEMENT_RETURN_ARG(If, row, col, (condition, if_statement, else_statement))
}

Statement* Parser::while_statement(){
	size_t row = GET_ROW(-1), col = GET_COL(-1);
	Expression* condition = expression();
	Statement* statement = statement_or_block();
	NEW_STATEMENT_RETURN_ARG(While, row, col, (condition, statement))
}

Statement* Parser::do_while_statement(){
	size_t row = GET_ROW(-1), col = GET_COL(-1);
	Statement* statement = statement_or_block(GET_KW(WHILE));
	Expression* condition = expression();
	NEW_STATEMENT_RETURN_ARG(DoWhile, row, col, (condition, statement))
}

Statement* Parser::for_statement(){

	size_t row = GET_ROW(-1), col = GET_COL(-1);
	int foreach_index = look_match_op(0, LPAREN) ? 1 : 0; // не обязательные скобки

	if(look_match(foreach_index, TT_IDENTIFIER)
		&& LOOK_MATCH_KW(foreach_index+1, IN)){
		return foreach_arr_statement(row, col, false);
	}

	if(look_match(foreach_index, TT_IDENTIFIER)
		&& look_match_op(foreach_index+1, COMMA)
		&& look_match(foreach_index+2, TT_IDENTIFIER)
		&& LOOK_MATCH_KW(foreach_index+3, IN)){
		return foreach_arr_statement(row, col, true);
	}

	bool open_parent = match_op(LPAREN); // не обязательные скобки

	Statement* initialization = assignment_statement();
	consume_op(COMMA);
	Expression* termintion = expression();
	consume_op(COMMA);
	Statement* incement = assignment_statement();

	if(open_parent) consume_op(RPAREN);

	Statement* statement = statement_or_block();

	NEW_STATEMENT_RETURN_ARG(For, row, col, (initialization, termintion, incement, statement))
}

Statement* Parser::use_statement(){
	size_t row = GET_ROW(-1), col = GET_COL(-1);
	if(look_match_op(0, LBRACKET)){
		Expression *elements = array();
		CONSUME_KW(IN);
		NEW_STATEMENT_RETURN_ARG(Use, row, col, (expression(), elements))
	} else {
		NEW_STATEMENT_RETURN_ARG(Use, row, col, (expression()))
	}
}

ForeachStatement* Parser::foreach_arr_statement(size_t& row, size_t&col ,bool two_vars = false){

	bool open_parent = match_op(LPAREN); // не обязательные скобки

	lets_str_t key = "";
	lets_str_t val = "";

	if(two_vars){
		key = consume(TT_IDENTIFIER).get_text();
		consume_op(COMMA);
		val = consume(TT_IDENTIFIER).get_text();
	} else {
		val = consume(TT_IDENTIFIER).get_text();
	}

	CONSUME_KW(IN);
	Expression* container = expression();

	if(open_parent) consume_op(RPAREN);

	Statement* body = statement_or_block();

	NEW_STATEMENT_RETURN_ARG(Foreach, row, col, (key, val, container, body))
}

FunctionDefineStatement* Parser::function_define(){
	// def name(arg1, arg2 = val): ... end || def name(args) <- expr
	size_t row = GET_ROW(-1), col = GET_COL(-1);
	lets_str_t name = consume(TT_IDENTIFIER).get_text();
	Arguments args = arguments();
	Statement* body = statement_body();
	NEW_STATEMENT_RETURN_ARG(FunctionDefine, row, col, (name, args, body))
}

// ClassDefineStatement* Parser::class_define(){
	/* class Name
			public:
				var = 1
				def func(a):
					return a + self.var
				end
			private:
				var2 = 1
				def func2(a):
					return a + self.var2
				end
		end
	*/

// 	size_t row = GET_ROW(-1), col = GET_COL(-1);
// 	lets_str_t name = consume(TT_IDENTIFIER).get_text();
// 	Statement* body = statement_body();
// 	NEW_STATEMENT_RETURN_ARG(ClassDefine, row, col, (name, body))

// }

Arguments Parser::arguments(){
	// (arg1, arg2, arg3 = expr1)
	Arguments arguments;
	bool start_optional_args = false;
	consume_op(LPAREN);
	while(!match_op(RPAREN)){
		lets_str_t name = consume(TT_IDENTIFIER).get_text();
		if(match_op(EQ)){
			start_optional_args = true;
			arguments.add_optional(name, variable(false));
		} else if (!start_optional_args){
			arguments.add_required(name);
		} else {
			throw ParseException("Required argument cannot be after optional", "Error parse", GET_ROW(-1), GET_COL(-1));
		}
		match_op(COMMA);
	}
	return arguments;
}

Statement* Parser::statement_body(){
	if(match_op(LTMINUS))
		NEW_STATEMENT_RETURN_ARG(Return, GET_ROW(-1), GET_COL(-1), (expression()))

	return statement_or_block();
}

Expression* Parser::function_chain(Expression *qualified_name_expr){
	// f1()()() || f1().f2().f3() || f1().key

	Expression* expr = function(qualified_name_expr);

	if(look_match_op(0, LPAREN)){
		return function_chain(expr);
	}

	if(look_match_op(0, DOT)){
		lets_vector_t<Expression* > indices = variable_suffix();
		if(indices.empty()) return expr;

		if(look_match_op(0, LPAREN)){
			// next function call
			return function_chain(new ContainerAccessExpression(expr, indices));
		}
		NEW_EXPRESSION_RETURN_ARG(ContainerAccess, expr->get_position_row(), expr->get_position_col(), (expr, indices))
	}

	return expr;
}

FunctionalExpression* Parser::function(Expression *qualified_name_expr){
	// function(arg1, arg2, ...)
	size_t row = GET_ROW(-1), col = GET_COL(-1);

	consume_op(LPAREN);

	FunctionalExpression* function = new FunctionalExpression(qualified_name_expr);
	function->set_position(row, col);
	while(!match_op(RPAREN)){
		function->add_arguments(expression());
		match_op(COMMA);
	}

	return function;
}

ClassExpression* Parser::class_expr(){
	// new Class(arg1, arg2, ...)
	size_t row = GET_ROW(0), col = GET_COL(0);
	ClassExpression* class_ = new ClassExpression(qualified_name());
	class_->set_position(row, col);
	consume_op(LPAREN);

	while(!match_op(RPAREN)){
		class_->add_arguments(expression());
		match_op(COMMA);
	}

	return class_;
}

Expression* Parser::array(){
	size_t row = GET_ROW(0), col = GET_COL(0);
	consume_op(LBRACKET);

	lets_vector_t<Expression*> elements;

	while(!match_op(RBRACKET)){
		elements.push_back(expression());
		match_op(COMMA);
	}

	NEW_EXPRESSION_RETURN_ARG(Array, row, col, (elements))
}

Expression* Parser::map_vals(){
	// {key1: value1, key2: value2, ...}
	size_t row = GET_ROW(0), col = GET_COL(0);
	consume_op(LBRACE);
	lets_map_t<Expression*, Expression*> elements;
	while(!match_op(RBRACE)){

		Expression* key = expression();
		consume_op(COLON);
		Expression* val = expression();

		elements[key] = val;
		match_op(COMMA);
	}

	NEW_EXPRESSION_RETURN_ARG(Map, row, col, (elements))
}

MatchExpression* Parser::match(){
	// match expression :
	//	case pattern1 result1
	//	case pattern2 if extr result2
	//	case pattern1:
	//		return result1
	//	defautl result_default
	// end

	Expression* expr = expression();
	lets_vector_t<MatchExpression::Pattern*> patterns;

	do {
		MatchExpression::Pattern* pattern = NULL;

		if (MATCH_KW(DEFAULT)){
			pattern = new MatchExpression::DefaultPattern();
			if (look_match_op(0, COLON)) {
				pattern->result = block();
				this->pos--;
			} else {
				pattern->result = new ReturnStatement(expression());
			}
		} else {
			CONSUME_KW(CASE);
			Token current = get(0);
			if (match(TT_NUMBER)) {
				// case 0.5: 
				pattern = new MatchExpression::ConstantPattern(
					new NumberValue(NS_Tools::create_number(current.get_text()))
				);
			} else if (match(TT_HEX_NUMBER)) {
				// case 0xABC123: 
				pattern = new MatchExpression::ConstantPattern(
					new NumberValue(std::stol(&current.get_text()[0u], 0, 16))
				);
			} else if (match(TT_OCTAL_NUMBER)) {
				// case 0123: 
				pattern = new MatchExpression::ConstantPattern(
					new NumberValue(std::stol(&current.get_text()[0u], 0, 8))
				);
			} else if (match(TT_BINARY_NUMBER)) {
				// case 0b010101: 
				pattern = new MatchExpression::ConstantPattern(
					new NumberValue(std::stol(&current.get_text()[0u], 0, 2))
				);
			} else if (match(TT_STRING)) {
				// case "text":
				pattern = new MatchExpression::ConstantPattern(
					new StringValue(current.get_text())
				);
			} else if (match(TT_IDENTIFIER)) {
				// case value: 
				pattern = new MatchExpression::VariablePattern(current.get_text());
			} else if (match_op(LBRACKET)) {
				// case [x :: xs]:
				MatchExpression::ListPattern *list_pattern = new MatchExpression::ListPattern();
				while (!match_op(RBRACKET)) {
					list_pattern->add(consume(TT_IDENTIFIER).get_text());
					match_op(COLONCOLON);
				}
				pattern = list_pattern;
			} else if (match_op(LPAREN)) {
				// case (1, 2):
				MatchExpression::TuplePattern* tuple_pattern = new MatchExpression::TuplePattern();
				while (!match_op(RPAREN)) {
					if (match_op(QUESTION)) {
						tuple_pattern->add_any();
					} else {
						tuple_pattern->add(expression());
					}
					match_op(COMMA);
				}
				pattern = tuple_pattern;
			}

			if (pattern == NULL) {
				throw ParseException("Wrong pattern in match expression: " + current.get_text());
			}
			if (MATCH_KW(IF)) {
				// case e if e > 0:
				pattern->opt_condition = expression();
			}

			if (look_match_op(0, COLON)) {
				pattern->result = this->block({GET_KW(CASE), GET_KW(DEFAULT), GET_KW(END)});
				this->pos--;
			} else {
				pattern->result = new ReturnStatement(expression());
			}
		}

		patterns.push_back(pattern);
	} while (!MATCH_KW(END));

	NEW_EXPRESSION_RETURN_ARG(Match, expr->get_position_row(), expr->get_position_col(), (expr, patterns))
}

Expression* Parser::expression(){
	return assignment();
}

Expression* Parser::assignment(){
	Expression* assignment = assignment_strict();

	if(assignment != NULL){
		return assignment;
	}

	return include_expression();
}

Expression* Parser::assignment_strict(){
	size_t position = this->pos;
	Expression* target_expr = qualified_name();
	if((target_expr == NULL) || !(dynamic_cast<Accessible*>(target_expr))){
		this->pos = position;
		return NULL;
	}


	u_tt_t current_op = get(0).get_op();

	if(ASSIGN_OPERATORS.find(current_op) == ASSIGN_OPERATORS.end()){
		this->pos = position;
		return NULL;
	}

	match_operator(current_op);

	NEW_EXPRESSION_RETURN_ARG(Assignment, GET_ROW(-1), GET_COL(-1), (ASSIGN_OPERATORS[current_op], dynamic_cast<Accessible*>(target_expr), expression()))
}

Expression* Parser::include_expression() {
	// include 'file.lets'
	// a = include 'file.lets'

	if (MATCH_KW(INCLUDE)) {
		NEW_STATEMENT_RETURN_ARG(Include, GET_ROW(-1), GET_COL(-1), (in_expression()))
	}

	return in_expression();
}

Expression* Parser::in_expression() {
	// 1 in [1, 2, 3]
	// 's' in "string"
	// 'x' => 1 in { 'x': 1, 'y' : 2 }
	Expression* result = ternary();

	if(match_op(EQGT)){
		lets_vector_t<Expression*> exprs = {result, ternary()};
		CONSUME_KW(IN);
		NEW_EXPRESSION_RETURN_ARG(In, result->get_position_row(), result->get_position_col(), (exprs, expression()))
	}

	if (MATCH_KW(IN)) {
		lets_vector_t<Expression*> exprs = {result};
		NEW_EXPRESSION_RETURN_ARG(In, result->get_position_row(), result->get_position_col(), (exprs, expression()))
	}

	return result;
}

Expression* Parser::ternary() {
	Expression* result = logicalOr();

	if (match_op(QUESTION)) {

		size_t row = GET_ROW(-2), col = GET_COL(-2);
		Expression* trueExpr = expression();
		consume_op(COLON);
		Expression* falseExpr = expression();

		NEW_EXPRESSION_RETURN_ARG(Ternary, row, col, (result, trueExpr, falseExpr))
	}

	return result;
}

Expression* Parser::logicalOr(){
	Expression* result = logicalAnd();
	while(true){
		if(match_op(BARBAR) or MATCH_KW(OR)){
			NEW_EXPRESSION_EQUAL_ARG(result, Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::OR, result, logicalAnd()))
			continue;
		}
		break;
	}
	return result;
}

Expression* Parser::logicalAnd(){
	Expression* result = bitwiseOr();
	while(true){
		if(match_op(AMPAMP) or MATCH_KW(AND)){
			NEW_EXPRESSION_EQUAL_ARG(result, Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::AND, result, bitwiseOr()))
			continue;
		}
		break;
	}
	return result;
}

Expression* Parser::bitwiseOr() {

	Expression* expression = bitwiseXor();

	while (true) {
		if (match_op(BAR)) {
			NEW_EXPRESSION_EQUAL_ARG(expression, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::OR, expression, bitwiseXor()))
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::bitwiseXor() {
	Expression* expression = bitwiseAnd();

	while (true) {
		if (match_op(CARET)) {
			NEW_EXPRESSION_EQUAL_ARG(expression, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::XOR, expression, bitwiseAnd()))
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::bitwiseAnd() {
	Expression* expression = equality();

	while (true) {
		if (match_op(AMP)) {
			NEW_EXPRESSION_EQUAL_ARG(expression, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::AND, expression, equality()))
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::equality(){
	Expression* result = conditional();

	if(match_op(EQEQ))
		NEW_EXPRESSION_RETURN_ARG(Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::EQUALS, result, conditional()))
	if(match_op(EXCLEQ))
		NEW_EXPRESSION_RETURN_ARG(Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::NOT_EQUALS, result, conditional()))

	if(match_op(EQEQEQ))
		NEW_EXPRESSION_RETURN_ARG(Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::I_EQUALS, result, conditional()))
	if(match_op(EXCLEQEQ))
		NEW_EXPRESSION_RETURN_ARG(Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::I_NOT_EQUALS, result, conditional()))

	return result;
}

Expression* Parser::conditional(){
	Expression* result = shift();

	while(true){
		if(match_op(LT)){
			NEW_EXPRESSION_EQUAL_ARG(result, Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::LT, result, shift()))
			continue;
		}
		if(match_op(LTEQ)){
			NEW_EXPRESSION_EQUAL_ARG(result, Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::LTEQ, result, shift()))
			continue;
		}
		if(match_op(GT)){
			NEW_EXPRESSION_EQUAL_ARG(result, Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::GT, result, shift()))
			continue;
		}
		if(match_op(GTEQ)){
			NEW_EXPRESSION_EQUAL_ARG(result, Conditional, GET_ROW(0), GET_COL(0), (ConditionalExpression::Operator::GTEQ, result, shift()))
			continue;
		}
		break;
	}

	return result;
}

Expression* Parser::shift() {
	Expression *expression = additive();

	while (true) {
		if (match_op(LTLT)) {
			NEW_EXPRESSION_EQUAL_ARG(
				expression, Binary,
				GET_ROW(0), GET_COL(0),
				(NS_Binary::Operator::LSHIFT, expression, additive())
			)
			continue;
		}
		if (match_op(GTGT)) {
			NEW_STATEMENT_EQUAL_ARG(
				expression, Expr,
				GET_ROW(0), GET_COL(0),
				(new BinaryExpression(NS_Binary::Operator::RSHIFT, expression, additive()))
			)
			continue;
		}
		break;
	}

	return expression;
}

Expression* Parser::additive(){
	Expression *result = multiplicative();

	while (true) {
		if (match_op(PLUS)) {
			NEW_EXPRESSION_EQUAL_ARG(result, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::ADD, result, multiplicative()))
			continue;
		}
		if (match_op(MINUS)) {
			NEW_EXPRESSION_EQUAL_ARG(result, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::SUBTRACT, result, multiplicative()))
			continue;
		}
		break;
	}

	return result;
}

Expression* Parser::multiplicative(){
	Expression *result = unary();

	while (true) {
		if (match_op(STAR)) {
			NEW_EXPRESSION_EQUAL_ARG(result, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::MULTIPLY, result, unary()))
			continue;
		}
		if (match_op(SLASH)) {
			NEW_EXPRESSION_EQUAL_ARG(result, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::DIVIDE, result, unary()))
			continue;
		}
		if (match_op(PERCENT)) {
			NEW_EXPRESSION_EQUAL_ARG(result, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::REMAINDER, result, unary()))
			continue;
		}
		if (match_op(STARSTAR)) {
			NEW_EXPRESSION_EQUAL_ARG(result, Binary, GET_ROW(0), GET_COL(0), (NS_Binary::Operator::POWER, result, unary()))
			continue;
		}
		break;
	}

	return result;
}

Expression* Parser::unary(){

	// if (match_op(AMP)) {
		// NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::INCREMENT_PREFIX, primary(true)))
		// dbg("pointer")
	// }
	if (match_op(PLUSPLUS)) {
		NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::INCREMENT_PREFIX, primary(true)))
	}
	if (match_op(MINUSMINUS)) {
		NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::DECREMENT_PREFIX, primary(true)))
	}
	if(match_op(MINUS)) {
		NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::NEGATE, primary(false)))
	}
	if (match_op(EXCL)) {
		NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::NOT, primary(false)))
	}
	if (MATCH_KW(NOT)) {
		NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::NOT, expression()))
	}
	if (match_op(TILDE)) {
		NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::COMPLEMENT, primary(false)))
	}
	if(match_op(PLUS)){
		return primary(false);
	}

	return primary(false);
}

Expression* Parser::primary(bool incr) {
	if(MATCH_KW(MATCH)){
		return match();
	}

	if(MATCH_KW(DEF)){
		size_t row = GET_ROW(-1), col = GET_COL(-1);
		Arguments args = arguments();
		Statement* statement = statement_body();
		NEW_EXPRESSION_RETURN_ARG(Value, row, col, (new UserDefineFunction(args, statement)))
	}

	if(MATCH_KW(NEW)){
		return class_expr();
	}

	return suffix(incr);
}

Expression* Parser::suffix(bool incr){
	Expression* var = variable(incr);

	lets_vector_t<Expression*> indices = value_suffix();

	if(!indices.empty()){
		NEW_EXPRESSION_EQUAL_ARG(var, ContainerAccess, var->get_position_row(), var->get_position_col(), (var, indices))
	}

	if(look_match_op(0, LPAREN)){
		return function_chain(var);
	}

	return var;
}

Expression* Parser::variable(bool incr) {

	if(match_op(LPAREN)){
		Expression* result = expression();
		consume_op(RPAREN);
		return result;
	}

	if(look_match(0, TT_IDENTIFIER) && look_match_op(1, LPAREN)){
		Expression* val;
		NEW_EXPRESSION_EQUAL_ARG(val, Value, GET_ROW(0), GET_COL(0), (consume(TT_IDENTIFIER).get_text()))
		return function_chain(val);
	}

	Expression* qualified_name_expr = qualified_name();

	if(qualified_name_expr != NULL){
		if(look_match_op(0, LPAREN)){
			return function_chain(qualified_name_expr);
		}
		if(!incr){
			if(match_op(PLUSPLUS)){
				NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::INCREMENT_POSTFIX, qualified_name_expr))
			}
			if(match_op(MINUSMINUS)){
				NEW_EXPRESSION_RETURN_ARG(Unary, GET_ROW(0), GET_COL(0), (UnaryExpression::Operator::DECREMENT_POSTFIX, qualified_name_expr))
			}
		}
		return qualified_name_expr;
	}

	if(look_match_op(0, LBRACKET)){
		return array();
	}

	if(look_match_op(0, LBRACE)){
		return map_vals();
	}

	return value();
}

Expression* Parser::qualified_name(){
	Token current = get(0);

	if(!match(TT_IDENTIFIER))
		return NULL;

	lets_vector_t<Expression*> indices = variable_suffix();
	if(indices.empty()){
		NEW_EXPRESSION_RETURN_ARG(Variable, current.get_row(), current.get_col(), (current.get_text()))
	}
	NEW_EXPRESSION_RETURN_ARG(ContainerAccess, current.get_row(), current.get_col(), (current.get_text(), indices))
}

lets_vector_t<Expression*> Parser::variable_suffix(){

	if(!look_match_op(0, DOT) && !look_match_op(0, LBRACKET)){
		return {};
	}

	lets_vector_t<Expression*> indices;
	while(look_match_op(0, DOT) || look_match_op(0, LBRACKET)){
		if(match_op(DOT)){
			Expression* key;
			NEW_EXPRESSION_EQUAL_ARG(key, Value, GET_ROW(-1), GET_COL(-1), (consume(TT_IDENTIFIER).get_text()))
			indices.push_back(key);
		}
		if(match_op(LBRACKET)){
			indices.push_back(expression());
			consume_op(RBRACKET);
		}
	}

	return indices;
}

lets_vector_t<Expression*> Parser::value_suffix(){

	if(!look_match_op(0, DOT)){
		return {};
	}

	lets_vector_t<Expression*> indices;
	while(match_op(DOT)){
		Expression* key;
		NEW_EXPRESSION_EQUAL_ARG(key, Value, GET_ROW(-1), GET_COL(-1), (consume(TT_IDENTIFIER).get_text()))
		indices.push_back(key);
	}

	return indices;
}

Expression* Parser::value() {

	Token current = this->get(0);

	if(match(TT_NUMBER)){
		NEW_EXPRESSION_RETURN_ARG(Value, current.get_row(), current.get_col(), (NS_Tools::create_number(current.get_text())))
	}

	if(match(TT_HEX_NUMBER)){
		NEW_EXPRESSION_RETURN_ARG(Value, current.get_row(), current.get_col(), ((long)std::stol(&current.get_text()[0u], 0, 16)))
	}
	if(match(TT_OCTAL_NUMBER)){
		NEW_EXPRESSION_RETURN_ARG(Value, current.get_row(), current.get_col(), ((long)std::stol(&current.get_text()[0u], 0, 8)))
	}
	if(match(TT_BINARY_NUMBER)){
		NEW_EXPRESSION_RETURN_ARG(Value, current.get_row(), current.get_col(), ((long)std::stol(&current.get_text()[0u], 0, 2)))
	}
	if(match(TT_STRING)){
		NEW_EXPRESSION_RETURN_ARG(Value, current.get_row(), current.get_col(), (current.get_text()))
	}

	throw ParseException("Unknown expression: " + current.get_text(), "Parser error", current.get_row(), current.get_col());
}



Token Parser::consume(u_tt_t type){

	Token current = get(0);

	if(type != current.get_type()){
		error_pars("Token " + current.to_s() + " dosn't match " + TOKEN_TO_STRING(type, ""), current);
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


Token Parser::consume_operator(u_tt_t op){

	Token current = get(0);

	if(current.get_type() != TT_OPERATOR or op != current.get_op()){
		error_pars("Token " + current.to_s() + " dosn't match '" + GET_OP_TO_S(op) + "'", current);
	}

	pos++;
	return current;
}

bool Parser::match_operator(u_tt_t op){

	Token current = get(0);
	if(current.get_type() != TT_OPERATOR or op != current.get_op()) return false;
	pos++;

	return true;
}

bool Parser::look_match_operator(int pos, u_tt_t op) {
	Token current = get(pos);
	return current.get_type() == TT_OPERATOR and current.get_op() == op;
}


Token Parser::consume_keyword(u_tt_t kw){

	Token current = get(0);

	if(current.get_type() != TT_KEYWORD or kw != current.get_kw()){
		error_pars("Token " + current.to_s() + " dosn't match " + GET_KW_TO_S(kw), current);
	}

	pos++;
	return current;
}

bool Parser::match_keyword(u_tt_t kw){

	Token current = get(0);
	if(current.get_type() != TT_KEYWORD or kw != current.get_kw()) return false;
	pos++;

	return true;
}

bool Parser::match_keywords(lets_vector_t<u_tt_t> keywords){

	Token current = get(0);

	bool res = false;
	for(auto kw: keywords){
		if(kw == current.get_kw()){
			res = true;
			break;
		}
	}

	if(res) pos++;
	return res;
}

bool Parser::look_match_keyword(int pos, u_tt_t kw) {
	Token current = get(pos);
	return current.get_type() == TT_KEYWORD and current.get_kw() == kw;
}


Token Parser::get(int rel_pos){
	size_t position = this->pos + rel_pos;

	if(position >= size){
		return TT_EOF_T;
	}
	return tokens.at(position);
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
	throw ParseException(text, "Parsing error", t.get_row(), t.get_col());
}

void Parser::error_pars(lets_str_t text, Node* n){
	throw ParseException(text, "Parsing error", n->get_position_row(), n->get_position_col());
}
