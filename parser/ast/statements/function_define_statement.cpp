#ifndef FUNCTION_DEFINE_STATEMENT_H
#define FUNCTION_DEFINE_STATEMENT_H

class FunctionDefineStatement : public Statement{
public:
	std::string name;
	std::vector<std::string> arg_names;
	Statement *body;
	bool is_constexpr;

	FunctionDefineStatement(
		std::string name,
		std::vector<std::string> arg_names,
		Statement *body,
		bool is_constexpr)
		:
		name(std::move(name)),
		arg_names(std::move(arg_names)),
		body(std::move(body)),
		is_constexpr(std::move(is_constexpr))
	{}

	void execute(){
		if(is_constexpr)
			Functions::set_constexpr(name, new UserDefineFunction(arg_names, body));
		else
			Functions::set(name, new UserDefineFunction(arg_names, body));
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		std::string result = "def " + name + " ( ";

		for (std::string argument : arg_names){
			result += argument;
			result +=  ", ";
		}

		result += "\b\b ) ";

		result += body->to_s();

		return result;
	}

	~FunctionDefineStatement(){
		// delete[] body;
	}
};

#endif
