//
//  lexer_regex.hpp
//  lex
//
//  Created by Mohamed Raslan on 26/03/2024.
//

#ifndef lexer_regex_hpp
#define lexer_regex_hpp

#include <stdio.h>
#include <string>
#include "lexer_regex.hpp"

class LexerRegex {
public:
    static bool matchBinaryOperator(const std::string& str);
    static bool matchUnaryOperator(const std::string& str);
    static bool matchlogicalOperator(const std::string& str);
    static bool matchBitwiseOperator(const std::string& str);
    static bool matchRelationalOperator(const std::string& str);
    static bool matchAssignmentOperator(const std::string& str);
    static bool matchTernaryOperator(const std::string& str);
    static bool matchKeyword(const std::string& str);
    static bool matchDatatype(const std::string& str);
    static bool matchFloat(const std::string& str);
    static bool matchBinary(const std::string& str);
    static bool matchHex(const std::string& str);
    static bool matchOctal(const std::string& str);
    static bool matchPunc(const std::string& str);
    static bool matchOperator(const std::string& str);
    
};
#endif /* lexer_regex_hpp */
