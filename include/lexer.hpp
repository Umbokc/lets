//
//  lexer.hpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <regex>


typedef unsigned int uint_t;

#include "main.h"
#include "token.hpp"
#include "tokentype.h"

// #include "exceptions_error.h"
// #include "lexer_exception.h"


class Lexer {
private:
    lets_str_t input, buffer;
    lets_vector_t<Token> tokens;
    uint_t pos, row, col, length;
    
    static lets_str_t OPERATORS_CHARS;
    static lets_map_t<lets_str_t, u_tt_t> OPERATORS;
    static lets_map_t<lets_str_t, u_tt_t> KEYWORDS;
    
public:
    Lexer() {}
    Lexer& operator=(const Lexer& r) { return *this; }
    
    Lexer(const lets_str_t& i) :input(std::move(i)) {
        pos = 0;
        row = 1;
        col = 1;
        length = (uint)i.length();
    }
    
    lets_vector_t<Token> tokenize();
    
    ~Lexer() {}
private:
    
    void tokenize_number();
    void tokenize_hex_number();
    int is_hex_number(char);
    void tokenize_binary_number();
    void tokenize_word();
    void tokenize_extended_word();
    void tokenize_text_double_quote();
    void tokenize_text_single_quote();
    void tokenize_operator();
    void tokenize_comment();
    void tokenize_multiline_comment();
    
    bool look_char(u_tt_t, char);
    char next();
    char peek(u_tt_t);
    
    void clear_buffer();
    bool is_word_var(char);
    void add_token(u_tt_t);
    void add_token(u_tt_t, lets_str_t);
    
    int find_c(lets_str_t, char);
//    void lexer_error(lets_str_t);
//    void lexer_error(lets_str_t, u_tt_t, int);
};

#endif /* lexer_hpp */
