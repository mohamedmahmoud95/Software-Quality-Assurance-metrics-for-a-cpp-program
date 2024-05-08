//
//  lexer.hpp
//  lex
//
//  Created by Mohamed Raslan on 27/03/2024.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "token_types.h"

struct Token {
    TokenType type;
    std::string lexeme;
};



class Lexer {
public:
    Lexer(const std::string& input);
    Token getNextToken();
    std::vector <int> numbers;
    std::vector <std::string> identifiers;

    
private:
    const std::string input;
    size_t position;
    std::string currentBuffer;
    std::string nextBuffer;
    const size_t bufferSize;
    
    void swapBuffers();
    
    std::string extractLexeme(const std::string& buffer);
    
    bool isDelimiter(char c);
    
    void handleToken(Token& token);
    
    void skipWhiteSpaces();

    void skipComments();

    bool isComment(const std::string& str);
    
    void skipNewLines();
};

#endif /* lexer_hpp */
