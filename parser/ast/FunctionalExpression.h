#ifndef FUNCTIONALEXPRESSION_H
#define FUNCTIONALEXPRESSION_H

class FunctionalExpression : public Expression{
private:
	std::string name;
	std::vector<Expression *> arguments; 
public:

	FunctionalExpression(std::string name){
		this->name = name;
	}
	
	FunctionalExpression(std::string name, std::vector<Expression *> arguments){
		this->name = name;
		this->arguments = arguments;
	}

	void addArguments(Expression *arg){
		arguments.push_back(arg);
	}

	Value *eval(){
		int size = arguments.size();
		std::vector<Value *> values;

		for (Expression *argument : arguments){
			values.push_back(argument->eval());
		}
		
		Function *function = Functions::get(name);
		
		if(Function* uf = dynamic_cast<UserDefineFunction*>(function)){
			
			UserDefineFunction *userFunction = dynamic_cast<UserDefineFunction*>(function);

			if(size != userFunction->getArgsCount()) throw std::runtime_error("Args count mismatch");
			
			Variables::push();

			for (int i = 0; i < size; ++i){
				Variables::set(userFunction->getArgName(i), values[i]);
			}
			Value *result = userFunction->execute(values);
			
			Variables::pop();
			return result;
		}

		return function->execute(values);

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
	~FunctionalExpression();
};

FunctionalExpression::~FunctionalExpression(){
}

#endif
