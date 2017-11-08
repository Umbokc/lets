//
//  lexer.cpp
//  lets
//
//  Created by Dragan Stepan on 30.10.17.
//  Copyright © 2017 umbokc. All rights reserved.
//

#include "../include/lexer.hpp"

#include "../include/ex_error.h"
#include "../include/ex_lexer.h"

lets_str_t Lexer::OPERATORS_CHARS = "+-*/%()[]{}=<>!&|,^~?:.@";
lets_map_t<lets_str_t, u_tt_t> Lexer::OPERATORS = {
    {"+", TT_PLUS},
    {"-", TT_MINUS},
    {"*", TT_STAR},
    {"/", TT_SLASH},
    {"%", TT_PERCENT},
    {"(", TT_LPAREN},
    {")", TT_RPAREN},
    {"[", TT_LBRACKET},
    {"]", TT_RBRACKET},
    {"{", TT_LBRACE},
    {"}", TT_RBRACE},
    {"=", TT_EQ},
    {"<", TT_LT},
    {">", TT_GT},
    {",", TT_COMMA},
    {".", TT_DOT},
    {"^", TT_CARET},
    {"~", TT_TILDE},
    {"?", TT_QUESTION},
    {":", TT_COLON},

    {"!", TT_EXCL},
    {"&", TT_AMP},
    {"|", TT_BAR},

    {"==", TT_EQEQ},
    {"!=", TT_EXCLEQ},
    {"<=", TT_LTEQ},
    {">=", TT_GTEQ},

    {"+=", TT_PLUSEQ},
    {"-=", TT_MINUSEQ},
    {"*=", TT_STAREQ},
    {"/=", TT_SLASHEQ},
    {"%=", TT_PERCENTEQ},
    {"&=", TT_AMPEQ},
    {"^=", TT_CARETEQ},
    {"|=", TT_BAREQ},

    {"++", TT_PLUSPLUS},
    {"--", TT_MINUSMINUS},

    {"::", TT_COLONCOLON},

    {"&&", TT_AMPAMP},
    {"||", TT_BARBAR},

    {"<<", TT_LTLT},
    {">>", TT_GTGT},

    {"@", TT_AT},
    {"..", TT_DOTDOT},
    {"**", TT_STARSTAR},
    {"<-", TT_LTMINUS},
};
lets_map_t<lets_str_t, u_tt_t> Lexer::KEYWORDS = {
    {"print", TT_KW_PRINT},
    {"put", TT_KW_PUT},
    {"if", TT_KW_IF},
    {"else", TT_KW_ELSE},
    {"while", TT_KW_WHILE},
    {"for", TT_KW_FOR},
    {"do", TT_KW_DO},
    {"break", TT_KW_BREAK},
    {"continue", TT_KW_CONTINUE},
    {"def", TT_KW_DEF},
    {"def_c", TT_KW_DEF_C},
    {"return", TT_KW_RETURN},
    {"use", TT_KW_USE},
    {"end", TT_KW_END},
    {"in", TT_KW_IN},
    {"include", TT_KW_RETURN},
    {"mode", TT_KW_MODE},
    {"self", TT_KW_SELF},
    {"match", TT_KW_MATCH},
    {"case", TT_KW_CASE},
    {"default", TT_KW_DEFAULT},
    {"and", TT_KW_AND},
    {"or", TT_KW_OR},
};

lets_vector_t<Token> Lexer::tokenize(){
    while (this->pos < this->length) {
        try{
            char current = peek(0);
            if(isdigit(current)) tokenize_number();
            else if(is_word_var(current)) tokenize_word();
            else if( current == '`') tokenize_extended_word();
            else if( current == '"' && look_char(1, '"') && look_char(2, '"')) tokenize_multiline_comment();
            else if( current == '"') tokenize_text_double_quote();
            else if( current == '\'') tokenize_text_single_quote();
            else if( current == '#') tokenize_comment();
            else if (find_c(OPERATORS_CHARS, current) != -1) tokenize_operator();
            else
                next();
        } catch(LexerException& le){
            std::cout << le.get_message() << std::endl;
            exit(0);
        }
    }
    
    return this->tokens;
}

void Lexer::tokenize_number() {
    
    clear_buffer();
    char current = peek(0);
    
    bool is_octal = (current == '0');
    
    if(is_octal && look_char(1, 'x')){
        tokenize_hex_number();
        return;
    }
    if(is_octal && look_char(1, 'b')){
        tokenize_binary_number();
        return;
    }
    
    while (true) {
        
        if(current == '.') {
            if(find_c(this->buffer, '.') != -1 || is_octal) throw LexerException(ExceptionsError::L_INVALID_FLOAT, this->row, this->col);
        } else if(current == '_') {
            current = next();
            continue;
        } else if(!isdigit(current)){
            break;
        }
        
        this->buffer.push_back(current);
        current = next();
    }
    
    if(is_octal && this->buffer.length() != 1){
        add_token(TT_OCTAL_NUMBER, this->buffer);
    } else {
        add_token(TT_NUMBER, this->buffer);
    }
}

void Lexer::tokenize_hex_number() {
    
    clear_buffer();
    next();
    next();
    
    char current = peek(0);
    
    while (is_hex_number(current) != -1) {
        this->buffer.push_back(current);
        current = next();
    }
    
    add_token(TT_HEX_NUMBER, this->buffer);
}

int Lexer::is_hex_number(char c){
    return find_c("0123456789abcdef", tolower(c, std::locale()));
}

void Lexer::tokenize_binary_number() {
    
    next();
    next();
    clear_buffer();
    
    char current = peek(0);
    lets_str_t cur_s;
    while (true) {
        cur_s = current;
        // cur_s.push_back(current);
        if(std::regex_match(cur_s, std::regex("^[01]+$")) == 0)
            break;
        
        this->buffer.push_back(current);
        current = next();
    }
    
    add_token(TT_BINARY_NUMBER, this->buffer);
}

void Lexer::tokenize_word() {
    
    clear_buffer();
    char current = peek(0);
    while (true) {
        if(!(isdigit(current) || is_word_var(current))){
            break;
        }
        
        this->buffer.push_back(current);
        current = next();
    }
    
    if(KEYWORDS.find(this->buffer) != KEYWORDS.end()){
        add_token(KEYWORDS[this->buffer]);
    } else {
        add_token(TT_IDENTIFIER, this->buffer);
    }
}

void Lexer::tokenize_extended_word() {
    next(); // skip `
    clear_buffer();
    char current = peek(0);
    
    int back_row = this->row;
    int back_col = this->col;
    
    while (true) {
        if (current == '`') break;
        if (current == '\0') throw LexerException(ExceptionsError::L_EOF_EXTEND_WORD, back_row, back_col);
        if (current == '\n' || current == '\r') throw LexerException(ExceptionsError::L_EOL_EXTEND_WORD, this->row, this->col);
        this->buffer.push_back(current);
        current = next();
    }
    next(); // skip closing `
    add_token(TT_IDENTIFIER, this->buffer);
}

void Lexer::tokenize_text_double_quote() {
    
    next();
    clear_buffer();
    
    char current = peek(0);
    
    int back_row = this->row;
    int back_col = this->col;
    while (true) {
        
        if(current == '\\'){
            current = next();
            switch (current) {
                case '\\': current = next(); this->buffer.push_back('\\'); continue;
                case '"': current = next(); this->buffer.push_back('\"'); continue;
                case 'n': current = next(); this->buffer.push_back('\n'); continue;
                case 't': current = next(); this->buffer.push_back('\t'); continue;
                case 'b': current = next(); this->buffer.push_back('\b'); continue;
                case 'r': current = next(); this->buffer.push_back('\r'); continue;
                case '0': current = next(); this->buffer.push_back('\0'); continue;
            }
            this->buffer.push_back('\\');
            continue;
        }
        
        if(current == '"') break;
        if (current == '\0') throw LexerException(ExceptionsError::L_REACHED_EOF, back_row, back_col);
        this->buffer.push_back(current);
        current = next();
    }
    
    next();
    
    add_token(TT_STRING , this->buffer);
}

void Lexer::tokenize_text_single_quote() {
    
    next();
    clear_buffer();
    
    char current = peek(0);
    
    int back_row = this->row;
    int back_col = this->col;
    
    while (true) {
        if(current == '\\'){
            current = next();
            switch (current) {
                case '\\': current = next(); this->buffer.push_back('\\'); continue;
                case '\'': current = next(); this->buffer.push_back('\''); continue;
            }
            this->buffer.push_back('\\');
            continue;
        }
        
        if(current == '\'') break;
        if (current == '\0') throw LexerException(ExceptionsError::L_REACHED_EOF, back_row, back_col);
        this->buffer.push_back(current);
        current = next();
    }
    
    next();
    
    add_token(TT_STRING, this->buffer);
}

void Lexer::tokenize_operator() {
    
    char current = peek(0);
    lets_str_t text;
    clear_buffer();
    
    while (true) {
        text = this->buffer;
        if(!text.empty() && OPERATORS.find(text + current) == OPERATORS.end()){
            // if(!text.empty() && find (OPERATORS.begin(), OPERATORS.end(), text + current) == OPERATORS.end()){
            add_token(OPERATORS[text], text);
            return;
        }
        
        this->buffer.push_back(current);
        current = next();
    }
}

void Lexer::tokenize_comment(){
    next();
    char current = peek(0);
    while (current != '\r' && current != '\n' && current != '\0') {
        current = next();
    }
}

void Lexer::tokenize_multiline_comment(){
    next(); next(); next();
    
    int back_row = this->row;
    int back_col = this->col;
    
    char current = peek(0);
    while (true) {
        if(current == '"' && look_char(1, '"') && look_char(2, '"')) break;
        if(current == '\0') throw LexerException(ExceptionsError::L_MISS_CLOSE_TAG, back_row, back_col);
        current = next();
    }
    
    next(); next(); next();
}

bool Lexer::look_char(u_tt_t rpos, char chr){
    return peek(rpos) == chr;
}

char Lexer::next(){
    this->pos++;
    char res = peek(0);
    
    if(res == '\n'){
        this->row++;
        this->col = 1;
    } else {
        this->col++;
    }
    
    return res;
}

char Lexer::peek(u_tt_t rpos){
    int position = this->pos + rpos;
    if(position >= this->length) return '\0';
    return this->input[position];
}

void Lexer::clear_buffer(){
    buffer = "";
}

bool Lexer::is_word_var(char c){
    return isalpha(c, std::locale()) || (c == '_') || (c == '$');
}

int Lexer::find_c(lets_str_t s, char c) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

void Lexer::add_token(u_tt_t tt){
	add_token(tt, "");
}

void Lexer::add_token(u_tt_t tt, lets_str_t txt){
    this->tokens.push_back(Token(tt, txt, this->row, this->col));
}
