#ifndef BLOCKSTATEMENT_H
#define BLOCKSTATEMENT_H

BlockStatement::BlockStatement(){
	
}

void BlockStatement::add(Statement *statement){
	statements.push_back(statement);
}

void BlockStatement::execute(){
	for(auto st : statements)
		st->execute();
}

void BlockStatement::accept(Visitor *visitor){
	visitor->visit(this);
}

std::string BlockStatement::to_s(){
	std::string result = "";

	for(auto st : statements){
		result += st->to_s();
		result.push_back('\n');
	}
	
	return result;
}

#endif
