#ifndef DOWHILESTATEMENT_H
#define DOWHILESTATEMENT_H


DoWhileStatement::DoWhileStatement(Expression *condition, Statement *statement){
	this->condition = condition;
	this->statement = statement;
}

void DoWhileStatement::execute(){
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

void DoWhileStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string DoWhileStatement::to_s(){
	std::string result = "do " + statement->to_s() + " while " + condition->to_s();
	return result;
}

#endif
