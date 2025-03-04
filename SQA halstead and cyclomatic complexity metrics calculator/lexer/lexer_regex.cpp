//
//  lexer_regex.cpp
//  lex
//
//  Created by Mohamed Raslan on 26/03/2024.
//

#include "lexer_regex.hpp"
#include <regex>


bool LexerRegex::matchOperator(const std::string& str) {
    bool match = false;
   if (LexerRegex::matchUnaryOperator(str) ||
       LexerRegex::matchRelationalOperator(str) ||
       LexerRegex::matchlogicalOperator(str) ||
       LexerRegex::matchBitwiseOperator(str) ||
       LexerRegex::matchAssignmentOperator(str) ||
       LexerRegex::matchBinaryOperator(str) ||
       LexerRegex::matchTernaryOperator(str)  ||
       str == "if" ||   str == "else"  ||  str == "for"
       
       )
   {
       match = true;
   }
           
       
       return match;
}

bool LexerRegex::matchUnaryOperator(const std::string& str) {
    // Regular expression pattern for unary operators:
    static const std::regex unaryOperatorPattern("\\+\\+|\\-\\-");
    return std::regex_match(str, unaryOperatorPattern);;
}

bool LexerRegex::matchRelationalOperator(const std::string& str) {
    static const std::regex relationalOpPattern("<=?|>=?|==|!=");
    return std::regex_match(str, relationalOpPattern);
}

bool LexerRegex::matchlogicalOperator(const std::string& str) {
    static const std::regex logicalOperatorPattern("\\&\\&|\\|\\||!");
    return std::regex_match(str, logicalOperatorPattern);
}

bool LexerRegex::matchBitwiseOperator(const std::string& str) {
    static const std::regex bitwiseOperatorPattern("&|\\||\\^|~");
    return std::regex_match(str, bitwiseOperatorPattern);
}


bool LexerRegex::matchAssignmentOperator(const std::string& str) {
    static const std::regex assignmentOpPattern("=|\\+=|\\-=|\\*=|/=|%=|&=|\\|=|\\^=|<<=|>>=");
    return std::regex_match(str, assignmentOpPattern);
}

bool LexerRegex::matchBinaryOperator(const std::string& str) {
    // Regular expression pattern for binary operators:
    static const std::regex binaryoperatorPattern("[\\+\\-\\*%]");
    return std::regex_match(str, binaryoperatorPattern);
}

bool LexerRegex::matchTernaryOperator(const std::string& str) {
    static const std::regex ternaryOpPattern("\\?\\:");
    return std::regex_match(str, ternaryOpPattern);
}

bool LexerRegex::matchKeyword(const std::string& str) {
    // Regular expression pattern for keywords:
    static const std::regex keywordPattern("\\b(auto|break|case|const|continue|default|do|else|enum|extern|for|goto|if|register|return|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b");
    return std::regex_match(str, keywordPattern);
}

bool LexerRegex::matchDatatype(const std::string& str) {
    // Regular expression pattern for datatypes:
    static const std::regex datatypePattern("\\b(int|float|double|long|short|char|string)\\b");
    return std::regex_match(str, datatypePattern);
}

bool LexerRegex::matchFloat(const std::string& str) {
    // Regular expression pattern for float numbers:
    static const std::regex floatPattern("\\b\\d+\\.\\d+(e[+-]?\\d+)?\\b");
    return std::regex_match(str, floatPattern);
}

bool LexerRegex::matchBinary(const std::string& str) {
    // Regular expression pattern for binary numbers:
    static const std::regex binaryPattern("\\b0[bB][01]+\\b");
    return std::regex_match(str, binaryPattern);
}

bool LexerRegex::matchHex(const std::string& str) {
    // Regular expression pattern for hexadecimal numbers:
    static const std::regex hexPattern("\\b0[xX][0-9a-fA-F]+\\b");
    return std::regex_match(str, hexPattern);
}

bool LexerRegex::matchOctal(const std::string& str) {
    // Regular expression pattern for octal numbers:
    static const std::regex octalPattern("\\b0[0-7]+\\b");
    return std::regex_match(str, octalPattern);
}

bool LexerRegex::matchPunc(const std::string& str) {
    // Regular expression pattern for punctuation:
    // static const std::regex PuncPattern("\\(|\\)|,|;|;\\{|\\}");
    static const std::regex PuncPattern("\\(|\\)|\\{|\\}|\\[|\\]|,|\\.|;|:|\\?|'|\"|`|\\\\|\\n|#");
    return std::regex_match(str, PuncPattern);
}
