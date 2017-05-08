#ifndef STATEMENT_H
#define STATEMENT_H

using namespace std;

class Statement : public Node{
public:
	virtual void execute() = 0; 
	virtual string to_s() = 0;
private:
};

// Declaration classes statement

class ArrayAssignmentStatement : public Statement{
public:
	Expression *expression;
	ArrayAccessExpression *array;

	ArrayAssignmentStatement(ArrayAccessExpression *array, Expression *expression);

	void execute();

	void accept(Visitor *visitor);

	string to_s();
	~ArrayAssignmentStatement();
};
ArrayAssignmentStatement::~ArrayAssignmentStatement(){
	delete[] expression;
	delete[] array;
}


class AssignmentStatement : public Statement{
public:
	string variable;
	Expression *expression;

	AssignmentStatement(string variable, Expression *expression);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~AssignmentStatement();
};
AssignmentStatement::~AssignmentStatement(){
	delete[] expression;
}


class BlockStatement : public Statement{
public:
	vector<Statement*> statements;

	BlockStatement();

	void add(Statement *statement);
	void execute();
	void accept(Visitor *visitor);
	string to_s();

	~BlockStatement();
};
BlockStatement::~BlockStatement(){
}

class BreakStatement : public Statement{
public:
	BreakStatement();
	void execute();
	void accept(Visitor *visitor);
	string to_s();
	~BreakStatement();
};


class ContinueStatement : public Statement{
public:

	ContinueStatement();

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~ContinueStatement();
};


class DoWhileStatement : public Statement{
public:
	Expression *condition;
	Statement *statement;

	DoWhileStatement(Expression *condition, Statement *statement);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~DoWhileStatement();
};
DoWhileStatement::~DoWhileStatement(){
	delete[] condition;
	delete[] statement;
}


class ForStatement : public Statement{
public:
	Statement *initialization;
	Expression *termination;
	Statement *increment;
	Statement *statement;

	ForStatement(Statement *initialization, Expression *termination, Statement *increment, Statement *statement);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~ForStatement();
};
ForStatement::~ForStatement(){
	delete[] initialization;
	delete[] termination;
	delete[] increment;
	delete[] statement;
}


class FunctionDefineStatement : public Statement{
public:
	string name;
	vector<string> argNames;
	Statement *body;
	
	FunctionDefineStatement(string name, vector<string> argNames, Statement *body);

	void execute();

	void accept(Visitor *visitor);

	string to_s();

	~FunctionDefineStatement();
};
FunctionDefineStatement::~FunctionDefineStatement(){
	delete[] body;
}

class FunctionStatement : public Statement{
public:
	FunctionalExpression *function;

	FunctionStatement(FunctionalExpression *function);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~FunctionStatement();
};
FunctionStatement::~FunctionStatement(){
	delete[] function;
}


class IfStatement : public Statement{
public:
	Expression *expression;
	Statement *ifStatement;
	Statement *elseStatement;

	IfStatement(Expression *expression, Statement *ifStatement, Statement *elseStatement);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~IfStatement();
};
IfStatement::~IfStatement(){
	delete[] expression;
	delete[] ifStatement;
	delete[] elseStatement;
}


class PrintStatement : public Statement{
public:
	Expression *expression;

	PrintStatement(Expression *expression);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~PrintStatement();
};
PrintStatement::~PrintStatement(){
	delete[] expression;
}


class ReturnStatement : public Statement{
public:
	Value *result;
	Expression *expression;

	ReturnStatement(Expression *expression);

	Value *getResult();

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~ReturnStatement();
};
ReturnStatement::~ReturnStatement(){
	delete[] result;
	delete[] expression;
}


class WhileStatement : public Statement{
public:
	Expression *condition;
	Statement *statement;

	WhileStatement(Expression *condition, Statement *statement);

	void execute();

	void accept(Visitor *visitor);
	
	string to_s();

	~WhileStatement();
};
WhileStatement::~WhileStatement(){
	delete[] condition;
	delete[] statement;
}

#endif