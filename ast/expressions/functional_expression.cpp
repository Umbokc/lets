#ifndef FUNCTIONAL_EXPRESSION_H
#define FUNCTIONAL_EXPRESSION_H
#include <iostream>
#include <algorithm>

class FunctionalExpression : public Expression, public Statement{
public:
	std::string function_name;
	Expression* function_expr;
	std::vector<Expression *> arguments; 

	FunctionalExpression(){}
	~FunctionalExpression(){}
	
	FunctionalExpression(Expression* function_expr) :function_expr(std::move(function_expr)){
		this->function_name = this->function_expr->to_s();
	}

	void add_arguments(Expression *arg){
		arguments.push_back(arg);
	}

	void execute(){
		eval();
	}

	Value *eval(){

		int size = arguments.size();
		std::vector<Value *> values;
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

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string name_to_s(){
		return this->function_expr->to_s();
	}

	std::string args_to_s(){
		return func::vector_to_s<Expression *>(arguments) ;
	}

	std::string to_s(){
		return name_to_s() + "( " + args_to_s() + " )";
	}

private:

	Function* consume_function(Expression *expr){

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
	
	Function* get_function(std::string key){
		
		if(Variables::is_exists_all(key)){
			Value* variable = Variables::get(key);
			if(variable->type() == Types::T_FUNCTION){
				return dynamic_cast<FunctionValue*>(variable)->get_value();
			}
		}
		
		if(Functions::is_exists(key)) return Functions::get(key);

		throw ParseException("Unknown function \"" + key + "\"");
	}

};
#endif
