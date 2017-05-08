#ifndef PARSER_H
#define PARSER_H

using namespace std;

void error_pars(string text, Token te){
	error(te.position() + " " + text);
}

class Parser {
private:
	Token T_EOF_ = Token(_EOF_, "", -1,-1);
	vector<Token> tokens;
	int pos, size;
public:
	Parser();

	Parser(vector<Token> tokens){
		pos = 0;
		this->tokens = tokens;
		size = tokens.size();
	}

	BlockStatement *parse(){
		BlockStatement *result = new BlockStatement();
		while(!match(_EOF_)){
			result->add(statement());
		}

		return result;
	}

	~Parser();
private:

	Statement *block(){
		BlockStatement *block = new BlockStatement();
		
		consume(_LBRACE_);
		while(!match(_RBRACE_)){
			block->add(statement());
		}

		return block;
	}

	Statement *statementOrBlock(){
		if(lookMatch(0, _LBRACE_)) return block();
		else return statement();
		// return statement();
	}

	Statement *statement(){
		if(match(_PRINT_)) 		return new PrintStatement(expression());
		if(match(_IF_)) 			return ifElse();
		if(match(_DO_)) 			return doWhileStatement();
		if(match(_WHILE_)) 		return whileStatement();
		if(match(_BREAK_)) 		return new BreakStatement();
		if(match(_CONTINUE_)) return new ContinueStatement();
		if(match(_RETURN_)) 	return new ReturnStatement(expression());
		// if(match(_USE_)) 			return new UseStatement(expression());
		if(match(_FOR_)) 			return forStatement();
		if(match(_DEF_)) 			return functionDefine();
		if (lookMatch(0, _WORD_) && lookMatch(1,_LPAREN_)) {
			return new FunctionStatement(thefunction());	
		}

		return assignmentStatement();
	}

	Statement *assignmentStatement(){
		// _WORD_ _EQ_
		if(lookMatch(0,_WORD_) && lookMatch(1, _EQ_)){
			string var = consume(_WORD_).getText();
			consume(_EQ_);
			return new AssignmentStatement(var, expression());
		}
		
		if(lookMatch(0,_WORD_) && lookMatch(1, _LBRACKET_)){
			ArrayAccessExpression *array = theelement();
			consume(_EQ_);
			return new ArrayAssignmentStatement(array, expression());
		}
		error_pars("Unknown statement", get(0));
	}

	Statement *ifElse(){
		
		Expression *condition = expression();
		Statement *ifStatement = statementOrBlock();
		Statement *elseStatemen;

		if(match(_ELSE_)){
			elseStatemen = statementOrBlock();
		} else {
			elseStatemen = NULL;
		}

		return new IfStatement(condition, ifStatement, elseStatemen);
	}

	Statement *whileStatement(){
		Expression *condition = expression();
		Statement *statement = statementOrBlock();
		return new WhileStatement(condition, statement);
	}

	Statement *doWhileStatement(){
		Statement *statement = statementOrBlock();
		consume(_WHILE_);
		Expression *condition = expression();
		return new DoWhileStatement(condition, statement);
	}

	Statement *forStatement(){
		
		match(_LPAREN_); // не обязательные скобки
		
		Statement *initialization = assignmentStatement();
		consume(_COMMA_);
		Expression *termintion = expression();
		consume(_COMMA_);
		Statement *incement = assignmentStatement();
		
		match(_RPAREN_); // не обязательные скобки

		Statement *statement = statementOrBlock();

		return new ForStatement(initialization, termintion, incement, statement);
	}
	
	FunctionDefineStatement *functionDefine(){
		string name = consume(_WORD_).getText();
		consume(_LPAREN_);
		vector<string> argNames;

		while(!match(_RPAREN_)){
			argNames.push_back(consume(_WORD_).getText());
			match(_COMMA_);
		}

		Statement *body = statementOrBlock();

		return new FunctionDefineStatement(name, argNames, body);
	}

	FunctionalExpression *thefunction(){
		string name = consume(_WORD_).getText();
		consume(_LPAREN_);

		FunctionalExpression *function = new FunctionalExpression(name);
		
		while(!match(_RPAREN_)){
			function->addArguments(expression());
			match(_COMMA_);
		}
		return function; 
	}

	Expression *array(){
		consume(_LBRACKET_);

		std::vector<Expression *> elements;
		
		while(!match(_RBRACKET_)){
			elements.push_back(expression());
			match(_COMMA_);
		}
		
		return new ArrayExpression(elements);
	}

	ArrayAccessExpression *theelement(){
		string variable = consume(_WORD_).getText();
		std::vector<Expression*> indices;

		do{
			consume(_LBRACKET_);
			indices.push_back(expression());
			consume(_RBRACKET_);
		} while(lookMatch(0, _LBRACKET_));

		return new ArrayAccessExpression(variable, indices);
	}

	Expression *expression(){
		return ternary();
	}

	Expression *ternary() {
		Expression *result = logicalOr();

		if (match(_QUESTION_)) {
			Expression *trueExpr = expression();
			consume(_COLON_);
			Expression *falseExpr = expression();
			return new TernaryExpression(result, trueExpr, falseExpr);
		}

		return result;
	}

	Expression *logicalOr(){
		Expression *result = logicalAnd();
		while(true){
			if(match(_BARBAR_)){
				result = new ConditionalExpression(ConditionalExpression::OR, result, logicalAnd());
				continue;
			}
			break;
		}
		return result;
	}

	Expression *logicalAnd(){
		Expression *result = bitwiseOr();
		while(true){
			if(match(_AMPAMP_)){
				result = new ConditionalExpression(ConditionalExpression::AND, result, bitwiseOr());
				continue;
			}
			break;
		}
		return result;
	}

	Expression *bitwiseOr() {

		Expression *expression = bitwiseXor();

		while (true) {
			if (match(_BAR_)) {
				expression = new BinaryExpression(BinaryExpression::OR, expression, bitwiseXor());
				continue;
			}
			break;
		}

		return expression;
	}

	Expression *bitwiseXor() {
		Expression *expression = bitwiseAnd();

		while (true) {
			if (match(_CARET_)) {
				expression = new BinaryExpression(BinaryExpression::XOR, expression, bitwiseAnd());
				continue;
			}
			break;
		}

		return expression;
	}

	Expression *bitwiseAnd() {
		Expression *expression = equality();

		while (true) {
			if (match(_AMP_)) {
				expression = new BinaryExpression(BinaryExpression::AND, expression, equality());
				continue;
			}
			break;
		}

		return expression;
	}

	Expression *equality(){
		Expression *result = conditional();
		if(match(_EQEQ_)){
			return new ConditionalExpression(ConditionalExpression::EQUALS, result, conditional());
		}
		if(match(_EXCLEQ_)){
			return new ConditionalExpression(ConditionalExpression::NOT_EQUALS, result, conditional());
		}
		return result;
	}

	Expression *conditional(){
		Expression *result = shift();

		while(true){
			if(match(_LT_)){
				result = new ConditionalExpression(ConditionalExpression::LT, result, shift());
				continue;
			}
			if(match(_LTEQ_)){
				result = new ConditionalExpression(ConditionalExpression::LTEQ, result, shift());
				continue;
			}
			if(match(_GT_)){
				result = new ConditionalExpression(ConditionalExpression::GT, result, shift());
				continue;
			}
			if(match(_GTEQ_)){
				result = new ConditionalExpression(ConditionalExpression::GTEQ, result, shift());
				continue;
			}
			break;
		}
		
		return result;
	}

	Expression *shift() {
		Expression *expression = additive();

		while (true) {
			if (match(_LTLT_)) {
				expression = new BinaryExpression(BinaryExpression::LSHIFT, expression, additive());
				continue;
			}
			if (match(_GTGT_)) {
				expression = new BinaryExpression(BinaryExpression::RSHIFT, expression, additive());
				continue;
			}
			if (match(_GTGTGT_)) {
				expression = new BinaryExpression(BinaryExpression::URSHIFT, expression, additive());
				continue;
			}
			break;
		}

		return expression;
	}

	Expression *additive(){

		Expression *result = multiplicative();

		while(true){
			if(match(_PLUS_)){
				result = new BinaryExpression(BinaryExpression::ADD, result, multiplicative());			
				continue;
			}
			if(match(_MINUS_)){
				result = new BinaryExpression(BinaryExpression::SUBTRACT, result, multiplicative());
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
				result = new BinaryExpression(BinaryExpression::MULTIPLY, result, unary());
				continue;
			}
			if(match(_SLASH_)){
				result = new BinaryExpression(BinaryExpression::DIVIDE, result, unary());
				continue;
			}
			if (match(_PERCENT_)) {
				result = new BinaryExpression(BinaryExpression::REMAINDER, result, unary());
				continue;
			}
			break;
		}
		return result;
	}

	Expression *unary(){
		if(match(_MINUS_)){
			return new UnaryExpression(UnaryExpression::NEGATE, primary());
		}
		if (match(_EXCL_)) {
			return new UnaryExpression(UnaryExpression::NOT, primary());
		}
		if (match(_TILDE_)) {
			return new UnaryExpression(UnaryExpression::COMPLEMENT, primary());
		}
		if(match(_PLUS_)){
			return primary();
		}

		return primary();
	}

	Expression *primary(){
		Token current = get(0);

		if(match(_NUMBER_)){
			return new ValueExpression(atof(&current.getText()[0u]));
		}
		if(match(_HEX_NUMBER_)){
			return new ValueExpression(stol(&current.getText()[0u], 0, 16));
		}
		if(lookMatch(0, _WORD_) && lookMatch(1,_LPAREN_)){
			return thefunction();
		}
		if(lookMatch(0, _WORD_) && lookMatch(1,_LBRACKET_)){
			return theelement();
		}
		if(lookMatch(0,_LBRACKET_)){
			return array();
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

		error_pars("Unknown expression:", get(0));
	}

	Token consume(TokenType type){
		Token current = get(0);
		if(type != current.getType()) error_pars("Token " + current.to_s() + " dosn't match " + TokenTypeText[type], current);
		pos++;
		return current;
	}

	bool match(TokenType type){
		Token current = get(0);
		if(type != current.getType()) return false;
		pos++;
		return true;
	}

	bool lookMatch(int pos, TokenType type) {
		return get(pos).getType() == type;
	}

	Token get(int relPos){
		int position = pos + relPos;
		if(position >= size) return T_EOF_;
		return tokens[position];
	}
};

Parser::~Parser(){
}

#endif
