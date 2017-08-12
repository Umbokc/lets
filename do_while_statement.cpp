#ifndef DO_WHILE_STATEMENT_H
#define DO_WHILE_STATEMENT_H

class DoWhileStatement : public Statement{
public:
	Expression *condition;
	Statement *statement;

	DoWhileStatement(
		Expression *condition,
		Statement *statement)
		:
		condition(std::move(condition)),
		statement(std::move(statement))
	{}

	void execute(){
		do {
			try{
				statement->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
			 	// continue;
			}
		}
		while(condition->eval()->as_number() != 0);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		
		std::string result = "do " + 
		statement->to_s() + 
		" while " + 
		condition->to_s();

		return result;
	}

	~DoWhileStatement(){
		// delete[] condition;
		// delete[] statement;
	}
};

#endif
