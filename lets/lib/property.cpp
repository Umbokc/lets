//
//  lets/lib/property.cpp
//  lets
//
//  Created by Dragan Stepan on 21.02.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#include "../../include/lib/value.hpp"
#include "../../include/lib/property.hpp"

Property::Property(){}
Property::Property(Value* v):value(std::move(v)), is_private(false), is_constant(false){}
Property::Property(Value* v, bool is_p, bool is_c):value(std::move(v)), is_private(is_p), is_constant(is_c){}
lets_str_t Property::to_s(){ return value->to_s(); }
Property::~Property(){}

