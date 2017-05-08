#ifndef FORSTATEMENT_H
#define FORSTATEMENT_H

ForStatement::ForStatement(Statement *initialization, Expression *termination, Statement *increment, Statement *statement){
	this->initialization = initialization;
	this->termination = termination;
	this->increment = increment;
	this->statement = statement;
}

void ForStatement::execute(){
	for(initialization->execute(); termination->eval()->asNumber() != 0; increment->execute()){
		try{
			statement->execute();
		} catch (BreakStatement *bs){
			break;
		} catch (ContinueStatement *cs){
				// continue;
		}
	}
}

void ForStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string ForStatement::to_s(){
	std::string result = "for " + initialization->to_s() + ", " + termination->to_s() + ", " + increment->to_s() + " " + statement->to_s();
	return result;
}

#endif
