//
//  e_binary_expr.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/tools.hpp"
#include "../include/e_binary_expr.hpp"
#include "../include/ex_parse.h"
#include "../include/l_array_value.hpp"
#include "../include/l_string_value.hpp"
#include "../include/ex_operation_is_not_supported.h"

    
BinaryExpression::BinaryExpression(NS_Binary::Operator operation, Expression* expr1, Expression* expr2):
    operation(std::move(operation)), expr1(std::move(expr1)), expr2(std::move(expr2)){}

Value * BinaryExpression::eval(){
    Value *value1 = expr1->eval();
    Value *value2 = expr2->eval();
    try{
        return eval(value1, value2);
    } catch (std::exception& e){
        throw e;
    }
}

// void BinaryExpression::accept(Visitor *visitor){
//     visitor->visit(this);
// }

// Node * BinaryExpression::accept_r(ResultVisitor* visitor){
//     return visitor->visit(this);
// }

// template<typename T> Node* BinaryExpression::accept_r_a(ResultVisitorWithArg<T>* visitor, T t){
//     return visitor->visit(this, t);
// }

lets_str_t BinaryExpression::to_s(){
    return NS_Tools::string_format(
                                   "[%s %s %s]",
                                   expr1->to_s().c_str(),
                                   NS_Binary::OperatorString[operation].c_str(),
                                   expr2->to_s().c_str()
                                   );
}

BinaryExpression::~BinaryExpression(){
    // delete[] expr1;
    // delete[] expr2;
}

Value *BinaryExpression::eval(Value *value1, Value *value2){
    try{
        switch (operation) {
            case NS_Binary::ADD: return BO_add(value1, value2);
            case NS_Binary::SUBTRACT: return BO_subtract(value1, value2);
            case NS_Binary::MULTIPLY: return BO_multiply(value1, value2);
            case NS_Binary::DIVIDE: return BO_divide(value1, value2);
            case NS_Binary::REMAINDER: return BO_remainder(value1, value2);
            case NS_Binary::AND: return BO_and(value1, value2);
            case NS_Binary::OR: return BO_or(value1, value2);
            case NS_Binary::XOR: return BO_xor(value1, value2);
            case NS_Binary::LSHIFT: return BO_lshift(value1, value2);
            case NS_Binary::RSHIFT: return BO_rshift(value1, value2);
            default:
                operation_is_not_supported();
        }
    } catch(ParseException& pe){
//        if(Mode_Programm::without_stop){
//            std::cout << "Error binary operation: " << pe.get_message() << std::endl;
//            return NumberValue::ZERO;
//        } else {
            throw ParseException(pe.get_message());
//        }
    }
    return NumberValue::ZERO;
}

Value *BinaryExpression::BO_add(Value *value1, Value *value2) {
    
    switch (value1->type()) {
        case Types::T_NUMBER:
            return BO_add(dynamic_cast<NumberValue *>(value1), value2);
        case Types::T_ARRAY:
            if(value2->type() == Types::T_ARRAY){
                return NS_ArrayValue::merge(
                                            dynamic_cast<ArrayValue *>(value1),
                                            dynamic_cast<ArrayValue *>(value2)
                                            );
            } else if(value2->type() == Types::T_STRING){
                return new StringValue(value1->as_string() + value2->as_string());
            }
            throw ParseException("Cannot merge non array value to array");
        case Types::T_STRING:
        default:
            return new StringValue(value1->as_string() + value2->as_string());
    }
    
    return NumberValue::ZERO;
}

Value *BinaryExpression::BO_add(NumberValue *value1, Value *value2) {
    switch (value2->type()) {
        case Types::T_STRING:{
            return new StringValue(
                                   value1->as_string() + value2->as_string()
                                   );
        }
        case Types::T_NUMBER:
        default:
            return new NumberValue(value1->as_number() + value2->as_number());
    }
    return NumberValue::ZERO;
}

Value *BinaryExpression::BO_subtract(Value *value1, Value *value2) {
    return new NumberValue(value1->as_number() - value2->as_number());
}

Value *BinaryExpression::BO_multiply(Value *value1, Value *value2) {
    
    switch (value1->type()) {
        case Types::T_NUMBER:{
            return new NumberValue(value1->as_number() * value2->as_number());
        }
        case Types::T_ARRAY:{
            int iterat = value2->as_int();
            
            lets_vector_t<Value *> temparr;
            lets_vector_t<Value *> arr = dynamic_cast<ArrayValue *>(value1)->get_all();
            
            temparr.reserve(arr.size() * iterat);
            
            for (int i = 0; i < iterat; ++i) {
                temparr.insert(temparr.end(), arr.begin(), arr.end());
            }
            
            return new ArrayValue(temparr);
        }
        case Types::T_STRING:{
            
            int iterat = value2->as_int();
            lets_str_t str = value1->as_string();
            lets_str_t result("");
            for (int i = 0; i < iterat; ++i){
                result += str;
            }
            return new StringValue(result);
        }
        default:
            operation_is_not_supported();
    }
    
    return NumberValue::ZERO;
}

Value *BinaryExpression::BO_divide(Value *value1, Value *value2) {
    // if(value2->as_number() == 0)
    // throw ParseException("Division by NumberValue::ZERO is undefined");
    // else
    return new NumberValue(value1->as_number() / value2->as_number());
    
    return NumberValue::ZERO;
}

Value *BinaryExpression::BO_remainder(Value *value1, Value *value2) {
    return new NumberValue(value1->as_int() % value2->as_int());
}

Value *BinaryExpression::BO_and(Value *value1, Value *value2) {
    return new NumberValue(value1->as_int() & value2->as_int());
}

Value *BinaryExpression::BO_or(Value *value1, Value *value2) {
    return new NumberValue(value1->as_int() | value2->as_int());
}

Value *BinaryExpression::BO_xor(Value *value1, Value *value2) {
    return new NumberValue(value1->as_int() ^ value2->as_int());
}

Value *BinaryExpression::BO_lshift(Value *value1, Value *value2) {
    switch (value1->type()) {
        case Types::T_NUMBER:
            return new NumberValue(value1->as_int() << value2->as_int());
        case Types::T_ARRAY:
            dynamic_cast<ArrayValue *>(value1)->add(value2);
            return value1;
        default:
            operation_is_not_supported();
    }
    
    return NumberValue::ZERO;
}

Value *BinaryExpression::BO_rshift(Value *value1, Value *value2) {
    // if(value1->type() == Types::T_ARRAY ){
    // 	dynamic_cast<ArrayValue *>(value1)->add_forward(value2);
    // 		if(value2->type() == Types::T_ARRAY){
    // 			dynamic_cast<ArrayValue *>(value1)->add_forward(value2);
    // 			return ArrayValue::merge(
    // 				dynamic_cast<ArrayValue *>(value2),
    // 				dynamic_cast<ArrayValue *>(value1)
    // 			);
    // 		} else {
    // 			throw ParseException("Cannot add element to non array value");
    // 		}
    // }
    
    if(value2->type() == Types::T_ARRAY){
        dynamic_cast<ArrayValue *>(value2)->add_forward(value1);
        return value2;
    }
    
    return new NumberValue(value1->as_int() >> value2->as_int());
}

void BinaryExpression::operation_is_not_supported(){
    throw OperationIsNotSupportedException(
        NS_Binary::OperatorString[operation]
    );
}
