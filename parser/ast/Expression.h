#ifndef EXPRESSION_H
#define EXPRESSION_H

using namespace std;

class Expression : public Node {
public:
	virtual Value* eval() = 0;
	virtual string to_s() = 0;
};

// Declaration classes expression

class ArrayAccessExpression : public Expression{
public:
	string variable;
	vector<Expression*> indices;

	ArrayAccessExpression(string variable, vector<Expression*> indices);

	Value * eval();
	void accept(Visitor *visitor);
	string to_s();

	ArrayValue *getArray();
	int lastIndex();
private:
	int index(int index);
	ArrayValue *consumeArray(Value *value);
};


class ArrayExpression : public Expression{
public:
	vector<Expression *> elements; 

	ArrayExpression(vector<Expression *> elements);

	Value *eval();

	void accept(Visitor *visitor);

	string to_s();

	~ArrayExpression();
};


class BinaryExpression : public Expression{
public:
	static enum Operator { ADD, SUBTRACT, MULTIPLY, DIVIDE, REMAINDER, AND, OR, XOR, LSHIFT, RSHIFT, URSHIFT} z;
	string OperatorText[11] =  { "+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>", ">>>" };

	Operator operation;
	Expression *expr1;
	Expression *expr2;

	BinaryExpression(Operator, Expression*, Expression *);

	Value * eval();

	void accept(Visitor *visitor);

	string to_s(); 

	~BinaryExpression();
private:
	bool isArrayValue(Value *value);
	bool isStringValue(Value *value);
};
BinaryExpression::~BinaryExpression(){
	delete[] expr1;
	delete[] expr2;
}


class ConditionalExpression : public Expression{
public:
	static enum Operator { PLUS, MINUS, MULTIPLY, DIVIDE, EQUALS, NOT_EQUALS, LT, LTEQ, GT, GTEQ, AND, OR } x;
	string OperatorText[12] =  { "+", "-", "*", "/", "==", "!=", "<", "<=", ">", ">=", "&&", "||" };

	Expression *expr1;
	Expression *expr2;
	Operator operation;

	ConditionalExpression(Operator, Expression*, Expression*);

	Value* eval();

	void accept(Visitor *visitor);

	string to_s();

	~ConditionalExpression();
};
ConditionalExpression::~ConditionalExpression(){
	delete[] expr1;
	delete[] expr2;
}


class FunctionalExpression : public Expression{
public:
	string name;
	vector<Expression *> arguments; 

	FunctionalExpression(string name);
	
	FunctionalExpression(string name, vector<Expression *> arguments);

	void addArguments(Expression *arg);

	Value *eval();

	void accept(Visitor *visitor);

	string to_s();
};


class UnaryExpression : public Expression{
public:
	static enum Operator { NEGATE, NOT, COMPLEMENT} z;
	string OperatorText[3] =  { "-", "!", "~"};

	Operator operation;
	Expression *expr1;

	UnaryExpression(Operator, Expression *);

	Value* eval();

	void accept(Visitor *visitor);

	string to_s();

	~UnaryExpression();
};
UnaryExpression::~UnaryExpression(){
	delete[] expr1;
}


class TernaryExpression : public Expression{
public:
	Expression *condition;
	Expression *trueExpr, *falseExpr;

	TernaryExpression(Expression *condition, Expression *trueExpr, Expression *falseExpr);

	Value* eval();

	void accept(Visitor *visitor);

	string to_s();

	~TernaryExpression();
};
TernaryExpression::~TernaryExpression(){
	delete[] condition;
	delete[] trueExpr;
	delete[] falseExpr;
}


class ValueExpression : public Expression{
public:
	Value* value;

	ValueExpression(double value);

	ValueExpression(string value);

	Value* eval();

	void accept(Visitor *visitor);

	string to_s();
	~ValueExpression();
};
ValueExpression::~ValueExpression(){
	delete[] value;
}


class VariableExpression : public Expression{
public:
	string name;

	VariableExpression(string name);

	Value* eval();

	void accept(Visitor *visitor);

	string to_s();

	~VariableExpression();
};

#endif
