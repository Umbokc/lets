#ifndef WHILE_STATEMENT_H
#define WHILE_STATEMENT_H

class WhileStatement : public Statement{
public:
	Expression *condition;
	Statement *statement;

	WhileStatement(
		Expression *condition,
		Statement *statement)
		:
		condition(std::move(condition)),
		statement(std::move(statement))
	{}

	void execute(){
		while(condition->eval()->as_number() != 0){
			try{
				statement->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
				// continue;
			}
		}
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		std::string result = "while " + 
		condition->to_s() + " " + statement->to_s();
		return result;
	}

	~WhileStatement(){
		// delete[] condition;
		// delete[] statement;
	}
};

#endif
