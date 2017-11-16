//
//  e_conditional_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 03.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/e_conditional_expr.hpp"
#include "../include/ex_execute.h"
#include "../include/tools.hpp"

ConditionalExpression::ConditionalExpression(
    NS_Conditional::Operator operation, Expression* expr1, Expression* expr2):
    operation(std::move(operation)), expr1(std::move(expr1)), expr2(std::move(expr2)){}

Value* ConditionalExpression::eval(){
    Value* value1 = expr1->eval();
    Value* value2 = expr2->eval();
    
    double number1, number2;
    
    // if(Value* v1 = dynamic_cast<StringValue*>(value1)){
    if(value1->type() == Types::T_STRING){
        number1 = lets_compare(value1->as_string(), value2->as_string());
        number2 = 0;
    } else {
        number1 = value1->as_number();
        number2 = value2->as_number();
    }
    
    bool result;
    
    switch(operation){
        case NS_Conditional::LT : result = (number1 < number2); break;
        case NS_Conditional::LTEQ : result = (number1 <= number2); break;
        case NS_Conditional::GT : result = (number1 > number2); break;
        case NS_Conditional::GTEQ : result = (number1 >= number2); break;
        case NS_Conditional::NOT_EQUALS : result = (number1 != number2); break;
        case NS_Conditional::EQUALS : result = (number1 == number2); break;
            
        case NS_Conditional::AND: result = (number1 != 0 && number2 != 0); break;
        case NS_Conditional::OR : result = (number1 != 0 || number2 != 0); break;
            
        default:
            throw ExecuteException("Operation is not supported");
    }
    
    return new NumberValue(result);
}

lets_str_t ConditionalExpression::to_s(){
    return NS_Tools::string_format(
                                   "[%s %s %s]",
                                   expr1->to_s().c_str(),
                                   NS_Conditional::OperatorString[operation].c_str(),
                                   expr2->to_s().c_str()
                                   );
}


ConditionalExpression::~ConditionalExpression(){
    // delete[] expr1;
    // delete[] expr2;
}
