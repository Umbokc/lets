//
//  include/main.h
//  lets
//
//  Created by Dragan Stepan on 29.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__main_h
#define include__main_h

#include "declaration.h"

#define lets_array_t lets_lib::Array
#define lets_vector_t std::vector
#define lets_map_t std::map
#define lets_str_t std::string
#define lets_s_ptr_t std::shared_ptr

#define u_tt_t unsigned int

#define to_str(x) std::to_string(x)

#define dbg(s) std::cout << "debug:" << (#s) << ": " << (s) << std::endl;
#define dbge(s) std::cout << "debug:" << (#s) << ": " << (s) << std::endl; exit(0);
#define lets_simple_output(s) std::cout << s;
#define lets_output(s) std::cout << s << std::endl;
#define lets_error(s) std::cout << s << std::endl; exit(1);
#define lets_ctos(c) lets_str_t(1, c);
#define lets_compare(t1, t2) (t1 > t2) ? 1 : (t1 > t2) ? -1 : 0;

#define FUNCS_ARGS lets_vector_t<Value *>

//#define dbg(s, b) std::cout << "debug: " << s << std::endl; if (b) exit(0);

#endif /* include__main_h */
