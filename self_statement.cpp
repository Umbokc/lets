#ifndef LL_SELF_STATEMENT_CPP
#define LL_SELF_STATEMENT_CPP
#include <string>



class SelfStatement {
public:
	std::vector<Value *> args;

	SelfStatement(std::vector<Value *> args):args(std::move(args)){}

	Value* eval(){
		try{
			execute();
		} catch(SelfStatementResponse * ssr){
			dbg("lol");
		}

		return NULL;
	}

	Value* execute(){
		throw  this;
		return NULL;
	}

	std::string to_s(){
		return "the to s ";
	}

	~SelfStatement(){}
};

#endif
