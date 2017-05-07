#ifndef DOWHILESTATEMENT_H
#define DOWHILESTATEMENT_H

class DoWhileStatement : public Statement{
private:
	Expression *condition;
	Statement *statement;
public:

	DoWhileStatement(Expression *condition, Statement *statement){
		this->condition = condition;
		this->statement = statement;
	}

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
		while(condition->eval()->asNumber() != 0);
	}
	
	std::string to_s(){
		std::string result = "do " + statement->to_s() + " while " + condition->to_s();
		return result;
	}

	~DoWhileStatement();
};
#endif
