//
//  lets/expressions/match_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

// #include <iostream> // for dbg

#include "../../include/expressions/match_expr.hpp"
#include "../../include/lib/number_value.hpp"
#include "../../include/lib/null_value.hpp"
#include "../../include/lib/variables.hpp"
#include "../../include/statements/return_stat.hpp"
#include "../../include/tools.hpp"
#include "../../include/exception/pattern_matching.h"

lets_str_t MatchExpression::Pattern::to_s() {
	lets_str_t sb;
	if (opt_condition != NULL) {
		sb += " if " + opt_condition->to_s();
	}
	sb += " if " + result->to_s();
	return sb;
}

MatchExpression::ConstantPattern::ConstantPattern(Value *pattern) :constant(std::move(pattern)) {}

lets_str_t MatchExpression::ConstantPattern::to_s() {
	return constant->to_s() + Pattern::to_s();
	// return constant->to_s().concat(super.tolets_str_t());
}

MatchExpression::VariablePattern::VariablePattern(lets_str_t pattern) :variable(std::move(pattern)){}

lets_str_t MatchExpression::VariablePattern::to_s() {
	return variable + Pattern::to_s();
	// return variable.concat(super.tolets_str_t());
}

MatchExpression::DefaultPattern::DefaultPattern(){}

lets_str_t MatchExpression::DefaultPattern::to_s() {
	return "default" + Pattern::to_s();
}

MatchExpression::ListPattern::ListPattern() {}

MatchExpression::ListPattern::ListPattern(lets_vector_t<lets_str_t> parts) :parts(std::move(parts)) {}

void MatchExpression::ListPattern::add(lets_str_t part) {
	parts.push_back(part);
}

lets_str_t MatchExpression::ListPattern::to_s() {
	return "[" + NS_Tools::vector_s_to_s(parts, " :: ") + "]";
}

MatchExpression::TuplePattern::TuplePattern() {}
MatchExpression::TuplePattern::TuplePattern(lets_vector_t<Expression*> parts):values(std::move(parts)) {}

void MatchExpression::TuplePattern::add_any() {
	values.push_back(NULL);
}

void MatchExpression::TuplePattern::add(Expression* value) {
	values.push_back(value);
}

lets_str_t MatchExpression::TuplePattern::to_s() {
	return "(" + NS_Tools::vector_to_s<Expression*>(values, ", ") + ")";
}

MatchExpression::MatchExpression(Expression * expression,  lets_vector_t<Pattern*> patterns)
	:expression(std::move(expression)), patterns(std::move(patterns)){}

void MatchExpression::execute(){
	eval();
}

Value *MatchExpression::eval(){
	Value *value = expression->eval();
	for (Pattern* p : patterns) {
		if (ConstantPattern *pattern = dynamic_cast<ConstantPattern*>(p)) {
			if (match(value, pattern->constant) && opt_matches(p)) {
				return eval_result(p->result);
			}
		}
		if (VariablePattern *pattern = dynamic_cast<VariablePattern*>(p)) {
			if (Variables::is_exists(pattern->variable)) {
				if (match(value, Variables::get(pattern->variable)) && opt_matches(p)) {
					return eval_result(p->result);
				}
			} else {
				Variables::define(pattern->variable, value);
				if (opt_matches(p)) {
					Value *result = eval_result(p->result);
					Variables::remove(pattern->variable);
					return result;
				}
				Variables::remove(pattern->variable);
			}
		}
		if ((value->type() == Types::T_ARRAY) && dynamic_cast<ListPattern*>(p)) {
			ListPattern *pattern = dynamic_cast<ListPattern*>(p);
			if (match_list_pattern(dynamic_cast<ArrayValue*>(value), pattern)) {
			// Clean up variables if matched
				Value *result = eval_result(p->result);
				for (lets_str_t var : pattern->parts) {
					Variables::remove(var);
				}
				return result;
			}
		}
		if ((value->type() == Types::T_ARRAY) && (dynamic_cast<TuplePattern*>(p))) {
			TuplePattern *pattern = dynamic_cast<TuplePattern*>(p);
			if (match_tuple_pattern(dynamic_cast<ArrayValue*>(value), pattern) && opt_matches(p)) {
				return eval_result(p->result);
			}
		}
		if (DefaultPattern *pattern = dynamic_cast<DefaultPattern*>(p)){
			return eval_result(p->result);
		}
	}
	return NullValue::THE_NULL;
	// throw PatternMatchingException("No pattern were matched");
}

lets_str_t MatchExpression::to_s(){
	return "";
	// return "[ " + NS_Tools::vector_to_s<Expression *>(expression, ", ") + " ]";
}

MatchExpression::~MatchExpression(){}

bool MatchExpression::match_tuple_pattern(ArrayValue* array, TuplePattern* p) {
	if (p->values.size() != array->size()) return false;

	int size = array->size();
	for (int i = 0; i < size; i++) {
			Expression* expr = p->values.at(i);
			if (expr != NULL) {
				Value* val = expr->eval();
				// dbg(val->to_s() + " = " + array->get(i)->to_s())
				if(!val->equals(array->get(i))){
					// dbg(expr->to_s() + " = " + val->to_s())
					return false;
				// } else {
					// dbg(val->to_s() + " = " + array->get(i)->to_s())
					// return false;
				}
			}
	}
	return true;

}

bool MatchExpression::match_list_pattern(ArrayValue* array, ListPattern* p) {
	lets_vector_t<lets_str_t> parts = p->parts;

	int parts_size = parts.size();
	int array_size = array->size();

	switch (parts_size) {
		case 0:{ // match [] { case []: ... }
			if ((array_size == 0) && opt_matches(p)) {
				return true;
			}
			return false;
		} case 1:{ // match arr { case [x]: x = arr ... }
			lets_str_t variable = parts.at(0);
			Variables::define(variable, array);
			if (opt_matches(p)) {
				return true;
			}
			Variables::remove(variable);
			return false;
		} default: { // match arr { case [...]: .. }
			if (parts_size == array_size) {
				// match [0, 1, 2] { case [a::b::c]: a=0, b=1, c=2 ... }
				return match_list_pattern_equals_size(p, parts, parts_size, array);
			} else if (parts_size < array_size) {
				// match [1, 2, 3] { case [head :: tail]: ... }
				return match_list_pattern_with_tail(p, parts, parts_size, array, array_size);
			}
			return false;
		}
	}
}

bool MatchExpression::match_list_pattern_equals_size(ListPattern* p, lets_vector_t<lets_str_t> parts, int parts_size, ArrayValue* array) {
	// Set variables
	for (int i = 0; i < parts_size; i++) {
		Variables::define(parts.at(i), array->get(i));
	}
	if (opt_matches(p)) {
		// Clean up will be provided after evaluate result
		return true;
	}
	// Clean up variables if no match
	for (lets_str_t var : parts) {
		Variables::remove(var);
	}
	return false;
}

bool MatchExpression::match_list_pattern_with_tail(ListPattern* p, lets_vector_t<lets_str_t> parts, int parts_size, ArrayValue* array, int array_size) {
	// Set element variables
	int last_part = parts_size - 1;
	for (int i = 0; i < last_part; i++) {
		Variables::define(parts.at(i), array->get(i));
	}
	// Set tail variable
	ArrayValue* tail = new ArrayValue(array_size - parts_size + 1);
	for (int i = last_part; i < array_size; i++) {
		tail->set(i - last_part, array->get(i));
	}
	Variables::define(parts.at(last_part), tail);
	// Check optional condition
	if (opt_matches(p)) {
		// Clean up will be provided after evaluate result
		return true;
	}
	// Clean up variables
	for (lets_str_t var : parts) {
		Variables::remove(var);
	}
	return false;
}

bool MatchExpression::match(Value *value, Value *constant) {
	if (value->type() != constant->type()) return false;
	return value->equals(constant);
}

bool MatchExpression::opt_matches(Pattern *pattern) {
	if (pattern->opt_condition == NULL) return true;
	return !NullValue::THE_NULL->equals(pattern->opt_condition->eval());
}

Value *MatchExpression::eval_result(Statement *s) {
	try {
		s->execute();
	} catch (ReturnStatement *ret) {
		return ret->get_result();
	}
	return NullValue::THE_NULL;
}
