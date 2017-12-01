//
//  e_match_expr.hpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef e_match_expr_hpp
#define e_match_expr_hpp

#include <string>
#include <vector>
#include "main.h"
#include "expression.h"
#include "statement.h"
#include "l_function.h"
#include "l_array_value.hpp"

class MatchExpression : virtual public Expression, virtual public Statement{
public:

	class Pattern {
	public:
		Statement *result;
		Expression *opt_condition = NULL;

		lets_str_t to_s();

		virtual ~Pattern(){}
	};

	class ConstantPattern : public Pattern {
	public:
		Value *constant;
		ConstantPattern(Value*);

		lets_str_t to_s();
	};

	class VariablePattern : public Pattern {
	public:
		lets_str_t variable;

		VariablePattern(lets_str_t);

		lets_str_t to_s();
	};

	class DefaultPattern : public Pattern {
	public:
		DefaultPattern();
		lets_str_t to_s();
	};

	class ListPattern : public Pattern {
	public:
		lets_vector_t<lets_str_t> parts;

		ListPattern();

		ListPattern(lets_vector_t<lets_str_t>);

		void add(lets_str_t);

		lets_str_t to_s();
	};

	class TuplePattern : public Pattern {
	public:
		lets_vector_t<Expression*> values;

		TuplePattern();
		TuplePattern(lets_vector_t<Expression*>);

		void add_any();

		void add(Expression* value);

		lets_str_t to_s();
	};

	Expression *expression;
	lets_vector_t<Pattern*> patterns;

	MatchExpression(Expression*,lets_vector_t<Pattern*>);

	void execute();

	Value *eval();

	LETS_VISITORS_FUCTION_ACCEPT_MACROS()

	lets_str_t to_s();

	~MatchExpression();

private:
	bool match_tuple_pattern(ArrayValue*, TuplePattern*);
	bool match_list_pattern(ArrayValue*, ListPattern*);
	bool match_list_pattern_equals_size(ListPattern*, lets_vector_t<lets_str_t>, int, ArrayValue*);
	bool match_list_pattern_with_tail(ListPattern*, lets_vector_t<lets_str_t>, int, ArrayValue*, int);
	bool match(Value*, Value*);
	bool opt_matches(Pattern*);
	Value *eval_result(Statement*);
};

#endif /* e_match_expr_hpp */
