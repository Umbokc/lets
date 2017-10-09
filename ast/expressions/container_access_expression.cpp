#ifndef CONTAINER_ACCESS_EXPRESSION_CPP
#define CONTAINER_ACCESS_EXPRESSION_CPP
#include <string>
#include <vector>

class ContainerAccessExpression : public Expression, public Accessible {
private:
	bool root_is_var;
public:
	Expression* root;
	std::vector<Expression*> indices;

	ContainerAccessExpression(){}

	ContainerAccessExpression
		(std::string variable, std::vector<Expression*> indices)
	{
		this->root = new VariableExpression(variable), 
		this->indices = indices;
	}

	ContainerAccessExpression
		(Expression* root, std::vector<Expression*> indices)
		:
		root(std::move(root)), indices(std::move(indices))
	{
		root_is_var = (dynamic_cast<VariableExpression*>(this->root)) ? true : false;
	}

	bool root_is_variable(){
		return root_is_var;
	}

	Expression *get_root(){
		return root;
	}

	Value *eval(){
		return get();
	}
	
	Value *get(){
		Value* container = get_container();
		Value* last = last_index();
		switch(container->type()){
			case Types::T_ARRAY:
				return dynamic_cast<ArrayValue*>(container)->get(last->as_int());
			case Types::T_STRING:
				return new StringValue(
					dynamic_cast<StringValue*>(container)->get_c(last->as_int())
				);
			case Types::T_MAP:
				return dynamic_cast<MapValue*>(container)->get(last);
			default:
				throw ParseException(
					"Array or map expected. Got " + TypesString[container->type()]
				);
		}
	}
	
	Value *set(Value* value){
		Value* container = get_container();
		Value* last = last_index();
		switch(container->type()){
			case Types::T_ARRAY:
				dynamic_cast<ArrayValue*>(container)->set(last->as_int(), value);
				return value;
			case Types::T_MAP:
				dynamic_cast<MapValue*>(container)->set(last, value);
				return value;
			default:
				throw ParseException(
					"Array or map expected. Got " + TypesString[container->type()]
				);
		}
	}

	Value* get_container(){
		Value* container = root->eval();
		int last_i = indices.size() - 1;
		for(int i = 0; i < last_i; ++i){
			Value* the_i = index(i);
			switch(container->type()){
				case Types::T_ARRAY :{
					int array_index = the_i->as_int();
					container = dynamic_cast<ArrayValue*> (container)->get(array_index);
					break;
				}
				case Types::T_MAP :{
					container = dynamic_cast<MapValue*> (container)->get(the_i);
					break;
				}
				default:
					throw ParseException("Array or map expected");
			}
		}
		return container;
	}

	Value* last_index() {
		return index(indices.size() - 1);
	}

	MapValue* consume_map(Value* value){
		if(value->type() != Types::T_MAP){
			throw ParseException("Map expected");
		}
		return dynamic_cast<MapValue*>(value);
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	template<class R> R accept_r(ResultVisitor<R>* visitor){
		return visitor->visit(this);
	}

	std::string to_s(){
		return root->to_s() + func::vector_to_s<Expression *>(indices, ".");
	}

	~ContainerAccessExpression(){}
private:
	Value* index(int i){
		return indices[i]->eval();
	}
};

#endif