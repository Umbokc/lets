#ifndef FUNCTION_DEFINE_STATEMENT_H
#define FUNCTION_DEFINE_STATEMENT_H

class FunctionDefineStatement : public Statement{
public:
	std::string name;
	Arguments args;
	Statement *body;
	bool is_constexpr;

	FunctionDefineStatement(
		std::string name,
		Arguments args,
		Statement *body,
		bool is_constexpr)
		:
		name(std::move(name)),
		args(std::move(args)),
		body(std::move(body)),
		is_constexpr(std::move(is_constexpr))
	{}

	void execute(){
		if(is_constexpr)
			Functions::set_constexpr(name, new UserDefineFunction(args, body));
		else
			Functions::set(name, new UserDefineFunction(args, body));
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		std::string result = "def " + name;
		result +=  " ( " + args.to_s() + " ) ";
		result += body->to_s();
		return result;
	}

	~FunctionDefineStatement(){
		// delete[] body;
	}
};

#endif
