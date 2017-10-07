#ifndef LETS_MODULE_STD_H
#define LETS_MODULE_STD_H

#include "std_functions.h"

namespace NS_LM_Std {

	void run() {
		Functions::set_lets_funcs("len", 				new NS_LM_F_Std::NS_LM_Fs_Len(), true);
		Functions::set_lets_funcs("echo", 		new NS_LM_F_Std::NS_LM_Fs_Echo(), true);
		Functions::set_lets_funcs("echo_nl", 			new NS_LM_F_Std::NS_LM_Fs_EchoNl(), true);
		Functions::set_lets_funcs("self", 			new NS_LM_F_Std::NS_LM_Fs_Self(), true);
		Functions::set_lets_funcs("newArray", 	new NS_LM_F_Std::NS_LM_Fs_NewArray(), true);
	}

}

#endif