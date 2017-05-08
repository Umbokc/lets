#ifndef WHILESTATEMENT_H
#define WHILESTATEMENT_H

WhileStatement::WhileStatement(Expression *condition, Statement *statement){
	this->condition = condition;
	this->statement = statement;
}

void WhileStatement::execute(){
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

void WhileStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string WhileStatement::to_s(){
	std::string result = "while " + condition->to_s() + " " + statement->to_s();
	return result;
}

#endif
