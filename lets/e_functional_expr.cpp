//
//  e_functional_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 04.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include <iostream>
#include "../include/e_functional_expr.hpp"
#include "../include/l_functions.hpp"
#include "../include/l_function_value.hpp"
#include "../include/l_variables.h"
#include "../include/l_call_stack.h"
#include "../include/tools.hpp"
#include "../include/ex_variable_does_not_exists.h"

FunctionalExpression::FunctionalExpression(){}
FunctionalExpression::~FunctionalExpression(){}

FunctionalExpression::FunctionalExpression(Expression* function_expr):
    function_expr(std::move(function_expr)){
    this->function_name = this->function_expr->to_s();
}

void FunctionalExpression::add_arguments(Expression *arg){
    arguments.push_back(arg);
}

void FunctionalExpression::execute(){
    eval();
}

Value *FunctionalExpression::eval(){
    
    int size = (int)arguments.size();
    FUNCS_ARGS values;
    values.reserve(size);
    
    for (Expression *argument : arguments){
        values.push_back(argument->eval());
    }
    
    Function *f = consume_function(function_expr);
    CallStack::enter(function_expr->to_s(), f);
    Value* result = f->execute(values);
    CallStack::exit();
    
    return result;
}

lets_str_t FunctionalExpression::name_to_s(){
    return this->function_expr->to_s();
}

lets_str_t FunctionalExpression::args_to_s(){
    return NS_Tools::vector_to_s(this->arguments, ", ") ;
}

lets_str_t FunctionalExpression::to_s(){
    return name_to_s() + "( " + args_to_s() + " )";
}


Function* FunctionalExpression::consume_function(Expression *expr){
    
    try{
        Value* value = expr->eval();
        if(value->type() == Types::T_FUNCTION){
            return dynamic_cast<FunctionValue*>(value)->get_value();
        }
        return get_function(value->as_string());
    } catch (VariableDoesNotExistsException& e){
        if(e.get_variable() == "")
            return get_function(this->function_name);
        return get_function(e.get_variable());
    }
}

Function* FunctionalExpression::get_function(lets_str_t key){

    if(Functions::is_exists(key)) return Functions::get(key);
    
    if(Variables::is_exists(key)){
        Value* variable = Variables::get(key);
        if(variable->type() == Types::T_FUNCTION){
            return dynamic_cast<FunctionValue*>(variable)->get_value();
        }
    }
    
    
    throw ParseException("Unknown function \"" + key + "\"");
}