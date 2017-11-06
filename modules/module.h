//
//  modules/module.h
//  lets
//
//  Created by Dragan Stepan on 06.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef modules__module_h
#define modules__module_h

#define CHECK_AND_DEFINE_FUNC_MODULE(F_NAME, F_CLASS) \
	if(name == F_NAME || name == "*"){ \
		Functions::set_lets_funcs(F_NAME, new F_##F_CLASS(), true); if(name != "*") return; \
	}

#define CHECK_AND_DEFINE_VAR_MODULE(V_NAME, M_VAR) \
	if(name == V_NAME || name == "*"){ \
		Variables::define_lets(V_NAME, M_VAR, true); if(name != "*") return; \
	}

class ModuleParentClassFunctions :  public Function{
public:
	ModuleParentClassFunctions(){}
	~ModuleParentClassFunctions(){}
	lets_str_t to_s(){
		return typeid(*this).name();
	}
};

#endif /* modules__module_h */

