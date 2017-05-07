#ifndef ARRAYASSIGNMENTSTATEMENT_H
#define ARRAYASSIGNMENTSTATEMENT_H

class ArrayAssignmentStatement : public Statement{
private:
	std::string variable;
	Expression *index;
	Expression *expression;
public:
	ArrayAssignmentStatement(std::string variable, Expression *index, Expression *expression){
		this->variable = variable;
		this->index = index;
		this->expression = expression;
	}

	void execute(){
		Value* var = Variables::get(variable);
		if(Value *v = dynamic_cast<ArrayValue*>(var)){
			ArrayValue *array =  dynamic_cast<ArrayValue*>(var); 
			array->set((int)index->eval()->asNumber(), expression->eval());
		} else {
			throw std::runtime_error("Array expected");
		}
	}
	
	std::string to_s(){
		return variable + "[" + index->to_s() + "] = " + expression->to_s();
	}

	~ArrayAssignmentStatement();
};
#endif
