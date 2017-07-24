#ifndef BLOCK_STATEMENT_CPP
#define BLOCK_STATEMENT_CPP
#include <string>
#include <vector>

class BlockStatement : virtual public Statement {
public:

	std::vector<Statement*> statements;

	BlockStatement(){}

	void add(Statement *statement){
		statements.push_back(statement);
	}

	void execute(){
		for(auto st : statements)
			st->execute();
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){
		std::string result = "";

		for(auto st : statements){
			result += st->to_s();
			result.push_back('\n');
		}

		return result;
	}

};

#endif