#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

class IfStatement : public Statement{
private:
	Expression *expression;
	Statement *ifStatement;
	Statement *elseStatement;
public:

	IfStatement(Expression *expression, Statement *ifStatement, Statement *elseStatement){
		this->expression = expression;
		this->ifStatement = ifStatement;
		this->elseStatement = elseStatement;
	}

	void execute(){
		double result = expression->eval()->asNumber();
		if(result != 0){
			ifStatement->execute();
		} else if(elseStatement != NULL){
			elseStatement->execute();
		}
	}
	
	std::string to_s(){
		std::string result = "";
		result += "if ";
		result += expression->to_s();
		result += " ";
		result += ifStatement->to_s();
		if(elseStatement != NULL){
			result += "\nelse ";
			result += elseStatement->to_s();
		}

		return result;
	}

	~IfStatement();
};
#endif
