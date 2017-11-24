//
//  include/utils/minifier.hpp
//  lets
//
//  Created by Dragan Stepan on 24.11.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__utils__minifier_hpp
#define include__utils__minifier_hpp

#include <string>
#include "../main.h"

class Minifier {
private:
	lets_str_t::size_type length;
	lets_str_t input, minified_code;
public:

	Minifier();
	Minifier(lets_str_t);
	~Minifier();

	static lets_str_t minify(lets_str_t);
	lets_str_t minify();

private:
	char next();
	char peek(lets_str_t::size_type);
};

#endif /* include__utils__minifier_hpp */

