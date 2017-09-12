#ifndef FOR_STATEMENT_H
#define FOR_STATEMENT_H

class ForStatement : public Statement{
public:
	Statement *initialization;
	Expression *termination;
	Statement *increment;
	Statement *statement;

	ForStatement(
		Statement *initialization,
		Expression *termination,
		Statement *increment,
		Statement *statement)
		:
		initialization(std::move(initialization)),
		termination(std::move(termination)),
		increment(std::move(increment)),
		statement(std::move(statement))
	{}

	void execute(){
		Variables::push();
		for(initialization->execute(); termination->eval()->as_number() != 0; increment->execute()){
			try{
				statement->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
				// continue;
			}
		}
		Variables::pop();
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){

		std::string result = "for " + 
		initialization->to_s() + ", " + 
		termination->to_s() + ", " + 
		increment->to_s() + " " + 
		statement->to_s();

		return result;
	}

	~ForStatement(){
		// delete[] initialization;
		// delete[] termination;
		// delete[] increment;
		// delete[] statement;
	}
};

#endif
