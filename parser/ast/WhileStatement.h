#ifndef WHILESTATEMENT_H
#define WHILESTATEMENT_H

class WhileStatement : public Statement{
private:
	Expression *condition;
	Statement *statement;
public:

	WhileStatement(Expression *condition, Statement *statement){
		this->condition = condition;
		this->statement = statement;
	}

	void execute(){
		while(condition->eval()->asNumber() != 0){
			try{
				statement->execute();
			} catch (BreakStatement *bs){
				break;
			} catch (ContinueStatement *cs){
				// continue;
			}
		}
	}
	
	std::string to_s(){
		std::string result = "while " + condition->to_s() + " " + statement->to_s();
		return result;
	}

	~WhileStatement();
};
#endif
