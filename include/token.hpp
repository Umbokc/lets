//
//  include/token.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef include__token_hpp
#define include__token_hpp

#include <string>
#include "main.h"

class Token {
private:
	u_tt_t type;
	u_tt_t kw;
	u_tt_t op;
	lets_str_t text;
	size_t row = 0, col = 0;
public:
	Token();
	Token& operator=(const Token&);

	Token(u_tt_t, u_tt_t, u_tt_t, lets_str_t, size_t, size_t );

	u_tt_t get_kw();
	void set_kw(const u_tt_t&);

	u_tt_t get_op();
	void set_op(const u_tt_t&);

	u_tt_t get_type();
	void set_type(const u_tt_t&);

	lets_str_t get_text();
	void set_text(const lets_str_t&);

	size_t get_row();
	void set_row(size_t);
	size_t get_col();
	void set_col(size_t);

	lets_str_t get_position();

	lets_str_t to_s();

	~Token();
};

#endif /* include__token_hpp */
