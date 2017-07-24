#ifndef LETS_MODULE_STD_H
#define LETS_MODULE_STD_H

#include "std_module_functions.h"

namespace Lets_Module_Std {

	void run() {
		Functions::set_lets_funcs("echo", new Lets_Modules_Std::Echo(), true);
		Functions::set_lets_funcs("newArray", new Lets_Modules_Std::NewArray(), true);
	}

}

#endif