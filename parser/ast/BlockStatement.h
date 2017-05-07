#ifndef BLOCKSTATEMENT_H
#define BLOCKSTATEMENT_H

class BlockStatement : public Statement{
private:
	std::vector<Statement*> statements;
public:

	BlockStatement(){
		
	}

	void add(Statement *statement){
		statements.push_back(statement);
	}

	void execute(){
		for(auto st : statements)
			st->execute();
	}

	std::string to_s(){
		std::string result = "";

		for(auto st : statements){
			result += st->to_s();
			result.push_back('\n');
		}
		
		return result;
	}

	~BlockStatement();
};
#endif
