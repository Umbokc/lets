#ifndef ASSIGNVALIDATOR_H
#define ASSIGNVALIDATOR_H

class AssignValidator : public AbstractVisitor{
public:

	void visit(AssignmentStatement *s){
		s->expression->accept(this);
		if(Variables::isExists(s->variable)){
			error("Cannon assign value to constant");
		}
	}

};
#endif