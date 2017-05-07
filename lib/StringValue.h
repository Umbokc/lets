#ifndef STRINGVALUE_H
#define STRINGVALUE_H

class StringValue : public Value{
	std::string value;
public:
	StringValue(std::string value){
		this->value = value;
	}
	
	double asNumber(){
		// try{
			return atof(&value[0u]);
		// } catch {
			// return 0;
		// }
	}
	
	std::string asString(){
		return value;
	}

	std::string to_s(){
		return asString();
	}

	~StringValue();
	
};
#endif