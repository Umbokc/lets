//
//  include/lib/value.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__lib__value_h
#define include__lib__value_h

#include <vector>
#include <string>
#include <map>
#include "../main.h"
#include "types.h"
#include "../exception/execute.h"

class Value;
class Function;
class BoolValue;
class NullValue;
class NumberValue;
class StringValue;
class ArrayValue;
class MapValue;
class ClassValue;
class FunctionValue;

class Variable{
public:
	Value *value;
	bool is_private;
	bool is_constant;

	Variable();

	Variable(Value*);
	Variable(Value*, bool, bool);
	lets_str_t to_s();
	~Variable();
};

class VariablesContainer {
public:

	lets_map_t<lets_str_t, Variable> variables;

	VariablesContainer();

	bool is_exists(const lets_str_t&);
	bool is_constant(const lets_str_t&);

	Value* get(const lets_str_t&);

	void set(const lets_str_t&, Value*);
	void set(const lets_str_t&, Variable);

	void remove(const lets_str_t&);

	size_t size();

	lets_str_t to_s();

	~VariablesContainer();
};


class Value {
protected:
	VariablesContainer properties;
	lets_str_t class_name = "";
public:

	virtual Value* construct() = 0;
	virtual Value* construct(FUNCS_ARGS) = 0;

	void set_class_name(const lets_str_t&);
	lets_str_t class_to_s();
	lets_str_t get_class_name();

	size_t get_count_vars();

	bool prop_exists(const lets_str_t&);

	void check_prop(const lets_str_t&);

	void check_prop_contant(const lets_str_t&);

	Value* get_prop(Value*);
	Value* get_prop(const lets_str_t&);

	void set_prop(Value*, Value*);
	void set_prop(const lets_str_t&, Value*);
	void set_prop(const lets_str_t&, Variable);

	void define_prop(Value*, Value*);
	void define_prop(const lets_str_t&, Value*);
	void define_prop(const lets_str_t&, Variable);

	virtual Value* get(Value*) = 0;
	virtual void set(Value*, Value*) = 0;

	virtual bool as_bool() = 0;
	virtual int as_int() = 0;
	virtual double as_number() = 0;
	virtual long as_long() = 0;
	virtual lets_str_t as_string() = 0;
	virtual lets_str_t to_s() = 0;

	virtual int len() = 0;
	virtual Types type() = 0;

	virtual bool equals(Value*) = 0;
	virtual int compareTo(Value *obj) = 0;

	//virtual ~Value();
};

#define DEFAULT_METHODS_OF_CLASS() \
	ADD_DEF_METHOD_TO_CLASS("type", Type, { \
		return new StringValue(TypesString[self->type()]); \
	}, "")

#define ADD_DEF_METHOD_TO_CLASS(L_NAME, NAME, BODY, TO_S_ARG) \
	class __Lets__Default__Method__##NAME : public Function{ \
	private: \
		Value* self; \
	public: \
		__Lets__Default__Method__##NAME(Value *s):self(std::move(s)){} \
		Value* execute(FUNCS_ARGS args) BODY \
		lets_str_t to_s(){ \
			return lets_str_t(L_NAME) + "(" + TO_S_ARG + ")"; \
		} \
	}; \
	this->define_prop(L_NAME, Variable(new FunctionValue(new __Lets__Default__Method__##NAME(this)), false, true));

#define ADD_METHOD_TO_CLASS(TYPE, L_NAME, NAME, BODY, TO_S_ARG) \
	class __Lets##TYPE##Method__##NAME : public Function{ \
	private: \
		TYPE##Value* self; \
	public: \
		__Lets##TYPE##Method__##NAME(TYPE##Value *s):self(std::move(s)){} \
		Value* execute(FUNCS_ARGS args) BODY \
		lets_str_t to_s(){ \
			return lets_str_t(L_NAME) + "(" + TO_S_ARG + ")"; \
		} \
	}; \
	this->define_prop(L_NAME, Variable(new FunctionValue(new __Lets##TYPE##Method__##NAME(this)), false, true));


#define LETS_REQUIRED_METHODS_VALUE_DECL() \
	Value* construct(); \
	Value* construct(FUNCS_ARGS); \
	bool as_bool(); \
	int as_int(); \
	double as_number(); \
	long as_long(); \
	lets_str_t as_string(); \
	lets_str_t to_s(); \
	int len(); \
	Types type(); \
	bool equals(Value* ); \
	int compareTo(Value *); \
	Value* get(Value*); \
	void set(Value*, Value*);


#endif /* include__lib__value_h */
