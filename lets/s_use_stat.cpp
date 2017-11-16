//
//  s_use_stat.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/s_use_stat.hpp"
#include "../include/ex_execute.h"

#include "../modules/std/std.hpp"
#include "../modules/math/math.hpp"
#include "../modules/type/type.hpp"

UseStatement::UseStatement(Expression* expr):expression(std::move(expr)), elements(NULL){}
UseStatement::UseStatement(Expression* expr, Expression* elems):expression(std::move(expr)), elements(std::move(elems)){}

void UseStatement::execute(){

	lets_str_t name = expression->eval()->to_s();

	ArrayValue* elems = NULL;

	if(elements != NULL){
		elems = dynamic_cast<ArrayValue*>(dynamic_cast<ArrayExpression*>(elements)->eval());
	}

   if(name == "std") LetsModule__std::run(elems);
   else if(name == "math") LetsModule__math::run(elems);
   else if(name == "type") LetsModule__type::run(elems);
   else
        throw ExecuteException("Does not found module " + name);
}

lets_str_t UseStatement::to_s(){
    return "use " + expression->to_s();
}

UseStatement::~UseStatement(){}

