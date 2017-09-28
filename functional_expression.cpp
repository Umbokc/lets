#ifndef FUNCTIONAL_EXPRESSION_H
#define FUNCTIONAL_EXPRESSION_H

class FunctionalExpression : public Expression, public Statement{
public:
	Expression* functionExpr;
	std::vector<Expression *> arguments; 

	FunctionalExpression(){}
	
	FunctionalExpression(Expression* functionExpr)
										:functionExpr(std::move(functionExpr)){}

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

		Function *f = consume_function(functionExpr);
		CallStack::enter(functionExpr->to_s(), f);
		Value* result = f->execute(values);
		CallStack::exit();
		return result;
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		std::string result = functionExpr->to_s() + "( ";

		for (Expression *argument : arguments){
			result += argument->to_s();
			result +=  ", ";
		}

		result +=  "\b\b )";

		return result;
	}

private:

	Function* consume_function(Expression* expr){
		try{
			Value* value = expr->eval();
			if(value->type() == Types::T_FUNCTION){
				return dynamic_cast<FunctionValue*>(value)->get_value();
			}
			return get_function(value->as_string());
		} catch (VariableDoesNotExistsException& e){
			return get_function(e.get_variable());
		}
	}
	
	Function* get_function(std::string key){
		if(Functions::is_exists(key)) return Functions::get(key);
		
		if(Variables::is_exists_all(key)){
			Value* variable = Variables::get(key);
			if(variable->type() == Types::T_FUNCTION){
				return dynamic_cast<FunctionValue*>(variable)->get_value();
			}
		}

		throw ParseException("Unknown function \"" + key + "\"");
	}

};
#endif
