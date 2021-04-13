#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum token_id {
    BEGIN_TK,                 // 0
    END_TK,                   // 1
    LOOP_TK,                  // 2
    WHILE_TK,                 // 3
    VOID_TK,                  // 4
    EXIT_TK,                  // 5
    GETTER_TK,                // 6
    OUTTER_TK,                // 7
    MAIN_TK,                  // 8
    IF_TK,                    // 9
    THEN_TK,                  // 10
    ASSIGN_TK,                // 11
    DATA_TK,                  // 12
    PROC_TK,                  // 13
    EQUALS_TK,                // 14
    EQUALS_OR_LESS_THAN_TK,   // 15
    EQUALS_OR_GREAT_THAN_TK,  // 16
    EQUALS_EQUALS_TK,         // 17
    COLON_TK,                 // 18
    COLON_EQUALS_TK,          // 19
    PLUS_TK,                  // 20
    MINUS_TK,                 // 21
    ASTERISK_TK,              // 22
    SLASH_TK,                 // 23
    PERCENT_TK,               // 24
    PERIOD_TK,                // 25
    LEFT_PAREN_TK,            // 26
    RIGHT_PAREN_TK,           // 27
    COMMA_TK,                 // 28
    LEFT_BRACE_TK,            // 29
    RIGHT_BRACE_TK,           // 30
    SEMI_COLON_TK,            // 31
    LEFT_BRACKET_TK,          // 32
    RIGHT_BRACKET_TK,         // 33
    ID_TK,                    // 34
    INT_TK,                   // 35
    EOF_TK,                   // 36
    ERROR_TK                  // 37
};

struct Token {
    unsigned int lineNum;      
    token_id token_ID;          
    std::string token_string;  

    Token(){
        this->token_ID = ERROR_TK;
        this->token_string = "";
        this->lineNum = 0;
    }
    
    Token(token_id ID, std::string string, unsigned int lineNum)
    {
        this->lineNum = lineNum;
        this->token_ID = ID;
        this->token_string = string;
    }
};

#endif