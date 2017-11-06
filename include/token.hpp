//
//  token.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <string>
#include "main.h"

class Token {
private:
    u_tt_t type;
    lets_str_t text;
    int row, col;
public:
    Token();
    Token& operator=(const Token&);
    
    Token(const u_tt_t&, const lets_str_t& , const int& , const int& );
    
    // type get/set
    u_tt_t get_type();
    void set_type(const int&);
    
    // test get/set
    lets_str_t get_text();
    void set_text(const lets_str_t&);
    
    // convert to string need data (token and text)
    lets_str_t to_s();
    
    int get_row();
    int get_col();
    
    lets_str_t get_position();
    
    ~Token();
};

#endif /* token_hpp */
