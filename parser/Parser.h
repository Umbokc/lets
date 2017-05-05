#ifndef PARSER
#define PARSER

#include "ast/Expression.h"
#include "ast/ValueExpression.h"
#include "ast/BinaryExpression.h"
#include "ast/UnaryExpression.h"
#include "ast/VariableExpression.h"
#include "ast/Statement.h"
#include "ast/AssignmentStatement.h"
#include "ast/PrintStatement.h"

using namespace std;

class Parser {
private:
	Token T_EOF_ = Token(_EOF_, "");
	vector<Token> tokens;
	int pos, size;
public:
	Parser();
	Parser(vector<Token> tokens){
		this->tokens = tokens;
		size = tokens.size();
	}

	vector<Statement*> parse(){
		vector<Statement*> result;	
		while(!match(_EOF_)){
			result.push_back(statement());
		}
		return result;
	}

	string to_s(){ 
		// return (TokenTypeText[type] + " " + text); 
	}
	~Parser();
private:

	Statement *statement(){
		if(match(_PRINT_)){
			return new PrintStatement(expression());
		}
		return assignmentStatement();
	}

	Statement *assignmentStatement(){
		// _WORD_ _EQ_
		Token current = get(0);
		if(match(_WORD_) && get(0).getType() == _EQ_){
			string variable = current.getText();
			consume(_EQ_);
			return new AssignmentStatement(variable, expression());
		}
		throw runtime_error("Unknown statement"); 
	}

	Expression *expression(){
		return additive();
	}

	Expression *additive(){
		Expression *result = multiplicative();

		while(true){
			if(match(_PLUS_)){
				result = new BinaryExpression('+', result, multiplicative());
				continue;
			}
			if(match(_MINUS_)){
				result = new BinaryExpression('-', result, multiplicative());
				continue;
			}
			break;
		}
		
		return result;
	}

	Expression *multiplicative(){
		Expression *result = unary();
		
		while(true){
			if(match(_STAR_)){
				result = new BinaryExpression('*', result, unary());
				continue;
			}
			if(match(_SLASH_)){
				result = new BinaryExpression('/', result, unary());
				continue;
			}
			break;
		}
		return result;
	}

	Expression *unary(){
		if(match(_MINUS_)){
			return new UnaryExpression('-', primary());
		}
		if(match(_PLUS_)){
			return primary();
		}

		return primary();
	}

	Expression *primary(){
		Token current = get(0);
		// debug("throw: " + current.getText());
		if(match(_NUMBER_)){
			return new ValueExpression(atof(&current.getText()[0u]));
		}
		if(match(_HEX_NUMBER_)){
			return new ValueExpression(stol(&current.getText()[0u], 0, 16));
		}
		if(match(_WORD_)){
			return new VariableExpression(current.getText());
		}
		if(match(_TEXT_)){
			return new ValueExpression(current.getText());
		}
		if(match(_LPAREN_)){
			Expression *result = expression();
			match(_RPAREN_);
			return result;
		}
		
		throw
			runtime_error("Unknown expression " + current.getText());
	}

	Token consume(TokenType type){
		Token current = get(0);
		if(type != current.getType()) throw runtime_error("Token " + current.to_s() + " dosn't match " + TokenTypeText[type]);
		pos++;
		return current;
	}

	bool match(TokenType type){
		Token  current = get(0);
		if(type != current.getType()) return false;
		pos++;
		return true;
	}

	Token get(int relativePosition){
		int position = pos + relativePosition;
		if(position >= size) return T_EOF_;
		// cout << tokens[position].to_s() << endl;
		return tokens[position];
	}
};

Parser::~Parser(){
	// delete expression();
	// delete additive();
	// delete multiplicative();
	// delete unary();
	// delete primary();
}


#endif