#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

class IfStatement : public Statement{
public:
	Expression *expression;
	Statement *if_statement;
	Statement *else_statement;

	IfStatement(
		Expression *expression,
		Statement *if_statement,
		Statement *else_statement)
		:
		expression(std::move(expression)),
		if_statement(std::move(if_statement)),
		else_statement(std::move(else_statement))
	{}

	void execute(){
		double result = expression->eval()->as_number();
		if(result != 0){
			if_statement->execute();
		} else if(else_statement != NULL){
			else_statement->execute();
		}
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		std::string result = "";
		result += "if ";
		result += expression->to_s();
		result += " ";
		result += if_statement->to_s();
		if(else_statement != NULL){
			result += "\nelse ";
			result += else_statement->to_s();
		}

		return result;
	}

	~IfStatement(){
		// delete[] expression;
		// delete[] if_statement;
		// delete[] else_statement;
	}
};

#endif
