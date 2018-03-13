//
//  argument.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/argument.hpp"

Argument::Argument() {}

Argument::Argument(lets_str_t name): name(std::move(name)), value_expr(NULL) {}

Argument::Argument(lets_str_t name, Expression* value_expr): name(std::move(name)), value_expr(std::move(value_expr)){}

lets_str_t Argument::get_name() {
		return name;
}
Expression *Argument::get_value_expr() {
		return value_expr;
}

lets_str_t Argument::to_s() {
		return name + (value_expr == NULL ? "" : " = " + value_expr->to_s());
}

Argument::~Argument() {}
