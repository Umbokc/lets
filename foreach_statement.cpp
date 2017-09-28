#ifndef FOREACH_STATEMENT_H
#define FOREACH_STATEMENT_H

class ForeachStatement : public Statement{
public:
	std::string key, val;
	Expression *container;
	Statement *body;

	ForeachStatement(
		std::string key,
		std::string val,
		Expression *container,
		Statement *body)
		:
		key(std::move(key)),
		val(std::move(val)),
		container(std::move(container)),
		body(std::move(body))
	{}

	void execute(){
		Value* objs = container->eval();
		bool has_key = key != "";

		Value *prev_var_value__key = (has_key && Variables::is_exists_all(key)) ? Variables::get(key) : NULL;
		Value *prev_var_value__val = Variables::is_exists_all(val) ? Variables::get(val) : NULL;

		int i = 0;
		if(dynamic_cast<StringValue*>(objs)){
			std::string str = dynamic_cast<StringValue*>(objs)->to_s();
			for(auto &entry : str){
				try{
					if(has_key){
						Variables::set(key, new NumberValue(i));
						i++;
					}

					Variables::set(val, new StringValue(entry));
					body->execute();
				} catch (BreakStatement *bs){
					break;
				} catch (ContinueStatement *cs){
					// continue;
				}
			}
		}
		if(dynamic_cast<ArrayValue*>(objs)){
			std::vector<Value *> arr = dynamic_cast<ArrayValue*>(objs)->get_all();
			for(Value *entry : arr){
				try{
					if(has_key){
						Variables::set(key, new NumberValue(i));
						i++;
					}
					Variables::set(val, entry);
					body->execute();
				} catch (BreakStatement *bs){
					break;
				} catch (ContinueStatement *cs){
					// continue;
				}
			}
		}
		if(dynamic_cast<MapValue*>(objs)){
			std::map<std::string, Value *> map = dynamic_cast<MapValue*>(objs)->get_all();
			for(auto &entry : map){
				try{
					Variables::set(key, new StringValue(entry.first));
					Variables::set(val, entry.second);
					body->execute();
				} catch (BreakStatement *bs){
					break;
				} catch (ContinueStatement *cs){
					// continue;
				}
			}
		}

		if(has_key && prev_var_value__key != NULL){
			Variables::set(key, prev_var_value__key);
		}
		if(prev_var_value__val != NULL){
			Variables::set(val, prev_var_value__val);
		}
	}

	void accept(Visitor *visitor){
		visitor->visit(this);
	}

	std::string to_s(){

		std::string result = "for ";
		result += (key != "") ? key + ", " : ""; 
		result += val + " in " +
			container->to_s() + " :\n" + 
			body->to_s() + "end";

		return result;
	}

	~ForeachStatement(){
	}
};

#endif
