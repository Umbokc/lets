//
//  include/lib/classes.hpp
//  lets
//
//  Created by Dragan Stepan on 11.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef include__lib__classes_hpp
#define include__lib__classes_hpp

#include <string>
#include <map>
#include "../main.h"

#include "number_value.hpp"
#include "class_value.hpp"

// class MainClass: public Class {
// public:
//   MainClass():Class("Main"){}
//   Value* construct(FUNCS_ARGS args){

//     // сделать чтобы эта строчка вызывалась автоматом при вызове функций класса
//     ClassValue* this_class = new ClassValue(this);

//     Class::set("main", args.at(0));
//     Variables::define_lets("this", this_class, true);

//     return this_class;
//   }

//   lets_str_t as_string(){
//     return "[ Main ]";
//   }

//   lets_str_t to_s(){
//     return as_string();
//   }
//   ~MainClass(){}
// };

// class Lets_Class_Array: public Class {
// public:

//   lets_vector_t<Value *> elements;

//   Lets_Class_Array():Class("Array"){
//     Class::set("size", new NumberValue(100));
//   }

//   Lets_Class_Array(size_t s): Lets_Class_Array(){
//     elements.resize(s);
//   }

//   Value* construct(FUNCS_ARGS args){

//     // this->add(NumberValue::ZERO);
//     // this->add(NumberValue::ZERO);
//     // this->add(NumberValue::ZERO);

//     // Class::set("size", new FunctionValue(new Lets_Class_Array_size(this)));

//     return new ClassValue(this);
//   }

//   void add(Value *val){
//     this->elements.push_back(val);
//   }

//   Value* get(Value* key){
//     if(key->type() == T_NUMBER)
//       return this->get(key->as_int());
//     else
//       return Class::get(key->as_string());
//   }

//   Value *get(int index){
//     if(index >= 0 && index < this->size())
//       return this->elements[index];
//     throw ExecuteException("Undefined index '"+to_str(index)+"' of array");
//   }

//   void set(Value *key, Value *val){
//     if(key->type() == T_NUMBER){
//       this->set(key->as_int(), val);
//       return;
//     }

//     variables[key->as_string()] = new Class_Variable(val);
//   }

//   void set(Value *key, Value *val, bool checking){
//     if(key->type() == T_NUMBER){
//       this->set(key->as_int(), val);
//       return;
//     }

//     if(checking) Class::check(key->as_string());
//     variables[key->as_string()] = new Class_Variable(val);
//   }

//   void set(int index, Value *value){
//     if(index > -1 && index < this->size()){
//       this->elements[index] = value;
//       return;
//     }
//     throw ExecuteException("Undefined index '"+ to_str(index) +"' of array");
//   }

//   int size(){
//     return (int)this->elements.size();
//   }

//   Types type(){
//     return Types::T_ARRAY;
//   }

//   lets_str_t as_string(){
//     return "[ " + NS_Tools::vector_to_s<Value *>(elements, ", ") + " ]";
//   }

//   lets_str_t to_s(){
//     return as_string();
//   }

//   ~Lets_Class_Array(){}
// };

class Classes{
public:
  static lets_map_t<lets_str_t, Value*> classes;

  static bool is_exists(lets_str_t);
  static Value* get(lets_str_t);
  static void set(lets_str_t, Value*);

};

#endif /* include__lib__classes_hpp */

