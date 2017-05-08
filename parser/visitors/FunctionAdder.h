#ifndef FUNCTIONADDER_H
#define FUNCTIONADDER_H

class FunctionAdder : public AbstractVisitor{
public:

	void visit(FunctionDefineStatement *s){
		s->body->accept(this);
		s->execute();
	}

};
#endif