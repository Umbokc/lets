#ifndef LETS_MODULE_TYPE_H
#define LETS_MODULE_TYPE_H

#include "type_functions.h"

namespace NS_LM_Type {

	void run() {
		Functions::set_lets_funcs("int", 			new NS_LM_F_Type::NS_LM_Fs_to_int(), true);
		Functions::set_lets_funcs("string", 	new NS_LM_F_Type::NS_LM_Fs_to_string(), true);
		Functions::set_lets_funcs("call_f", 	new NS_LM_F_Type::NS_LM_Fs_call_func(), true);
	}

}

#endif