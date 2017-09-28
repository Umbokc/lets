#ifndef LETS_MODULE_TYPE_H
#define LETS_MODULE_TYPE_H

#include "type_functions.h"

namespace Lets_Module_Type {

	void run() {
		Functions::set_lets_funcs("int", new NSLM_Type_Funcs::to_int(), true);
		Functions::set_lets_funcs("string", new NSLM_Type_Funcs::to_string(), true);
	}

}

#endif