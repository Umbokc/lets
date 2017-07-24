#ifndef ARRAY_ACCESS_EXPRESSION_CPP
#define ARRAY_ACCESS_EXPRESSION_CPP
#include <string>
#include <vector>

class ArrayAccessExpression : public Expression{
public:
	std::string variable;
	std::vector<Expression*> indices;

	ArrayAccessExpression(std::string variable,
					std::vector<Expression*> indices):
		variable(std::move(variable)), indices(std::move(indices)){}

	Value * eval(){
		return get_array()->get(last_index());
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){ 
		// return variable + "[" + index->to_s() + "]";

		std::string result = variable + "";

		for (Expression *index : indices){
			result += index->to_s();
			result +=  ", ";
		}

		result +=  "\b\b ";

		return result;
	}

	ArrayValue * get_array(){
		ArrayValue *array = consume_array(Variables::get(variable));

		int last = indices.size() - 1;
		for (int i = 0; i < last; ++i){
			array = consume_array(array->get(index(i)));
		}
		return array;
	}

	int last_index(){
		return index(indices.size() - 1);
	}

private:
	int index(int index){
		return (int)indices[index]->eval()->as_number();
	}

	ArrayValue *consume_array(Value *value){
		if(Value *v = dynamic_cast<ArrayValue*>(value)){
			return dynamic_cast<ArrayValue*>(value);
		} else {
			throw ParseException("Array expected");
		}
	}
};

#endif