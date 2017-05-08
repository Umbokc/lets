#ifndef VARIABLESPRINT_H
#define VARIABLESPRINT_H

class VariablesPrint : public AbstractVisitor{
public:

	void visit(AssignmentStatement *s){
		s->expression->accept(this);
		dbg(s->variable);
	}

	void visit(VariableExpression *s){
		dbg(s->name);
	}

};
#endif