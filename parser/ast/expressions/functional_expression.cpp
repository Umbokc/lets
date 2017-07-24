#ifndef FUNCTIONAL_EXPRESSION_H
#define FUNCTIONAL_EXPRESSION_H

class FunctionalExpression : public Expression{
public:
	std::string name;
	vector<Expression *> arguments; 

	FunctionalExpression( std::string name)
										:name(std::move(name)){}

	FunctionalExpression(
		std::string name,
		std::vector<Expression *> arguments)
		:
		name(std::move(name)),
		arguments(std::move(arguments))
	{}

	void add_arguments(Expression *arg){
		arguments.push_back(arg);
	}

	Value *eval(){
		int size = arguments.size();
		std::vector<Value *> values;

		for (Expression *argument : arguments){
			values.push_back(argument->eval());
		}

		Function *function = Functions::get(name);

		if(UserDefineFunction *userFunction = dynamic_cast<UserDefineFunction*>(function)){

			if(size != userFunction->get_args_count()) throw ParseException("Args count mismatch");

			Variables::push();

			for (int i = 0; i < size; ++i){
				Variables::set(userFunction->get_arg_name(i), values[i]);
			}
			Value *result = userFunction->execute(values);

			Variables::pop();
			return result;
		}

		return function->execute(values);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		std::string result = name + "( ";

		for (Expression *argument : arguments){
			result += argument->to_s();
			result +=  ", ";
		}

		result +=  "\b\b )";

		return result;
	}
};
#endif
