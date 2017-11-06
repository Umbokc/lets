//
//  e_match_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_match_expr.hpp"
#include "../include/l_number_value.hpp"
#include "../include/s_return_stat.hpp"
#include "../include/tools.hpp"


ANY_EXPR::ANY_EXPR(){}
Value *ANY_EXPR::eval() {
    return NumberValue::ONE;
}

lets_str_t ANY_EXPR::to_s() {
    return "_";
    // return "_".concat(super.toString());
}
ANY_EXPR::~ANY_EXPR(){}



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
    return constant->to_s();
    // return constant->to_s().concat(super.toString());
}

MatchExpression::VariablePattern::VariablePattern(lets_str_t pattern) :variable(std::move(pattern)){}

lets_str_t MatchExpression::VariablePattern::to_s() {
    return variable;
    // return variable.concat(super.toString());
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
    values.push_back(new ANY_EXPR());
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
    // Value *value = expression->eval();
    // for (Pattern* p : patterns) {
    // if (dynamic_cast<ConstantPattern*>(p)) {
    // 	ConstantPattern *pattern = dynamic_cast<ConstantPattern*>(p);
    // 	if (match(value, pattern->constant) && opt_matches(p)) {
    // 		return eval_result(p->result);
    // 	}
    // }
    // if (dynamic_cast<VariablePattern*>(p)) {
    // 	VariablePattern *pattern = dynamic_cast<VariablePattern*>(p);
    // 	if (pattern->variable == "_") return eval_result(p->result);
    
    // 	if (Variables::is_exists(pattern->variable)) {
    // 		if (match(value, Variables::get(pattern->variable)) && opt_matches(p)) {
    // 			return eval_result(p->result);
    // 		}
    // 	} else {
    // 		Variables::define(pattern->variable, value);
    // 		if (opt_matches(p)) {
    // 			Value *result = eval_result(p->result);
    // 			Variables::remove(pattern->variable);
    // 			return result;
    // 		}
    // 		Variables::remove(pattern->variable);
    // 	}
    // }
    // if ((value.type() == Types.ARRAY) && (dynamic_cast<ListPattern*>(p))) {
    // 	ListPattern *pattern = dynamic_cast<ListPattern*>(p);
    // 	if (matchListPattern((ArrayValue) value, pattern)) {
    // 		// Clean up variables if matched
    // 		Value *result = eval_result(p->result);
    // 		for (String var : pattern->parts) {
    // 			Variables::remove(var);
    // 		}
    // 		return result;
    // 	}
    // }
    // if ((value.type() == Types.ARRAY) && (dynamic_cast<TuplePattern*>(p))) {
    // 	TuplePattern *pattern = dynamic_cast<TuplePattern*>(p);
    // 	if (matchTuplePattern((ArrayValue) value, pattern) && opt_matches(p)) {
    // 		return eval_result(p->result);
    // 	}
    // }
    // }
    // throw new PatternMatchingException("No pattern were matched");
    return NULL;
}

lets_str_t MatchExpression::to_s(){
    return "";
    // return "[ " + NS_Tools::vector_to_s<Expression *>(expression, ", ") + " ]";
}

MatchExpression::~MatchExpression(){}

bool MatchExpression::match(Value *value, Value *constant) {
    if (value->type() != constant->type()) return false;
    return value->equals(constant);
    // return true;
}

bool MatchExpression::opt_matches(Pattern *pattern) {
    if (pattern->opt_condition == NULL) return true;
    return pattern->opt_condition->eval() != NumberValue::ZERO;
}

Value *MatchExpression::eval_result(Statement *s) {
    try {
        s->execute();
    } catch (ReturnStatement *ret) {
        return ret->get_result();
    }
    return NumberValue::ZERO;
}
