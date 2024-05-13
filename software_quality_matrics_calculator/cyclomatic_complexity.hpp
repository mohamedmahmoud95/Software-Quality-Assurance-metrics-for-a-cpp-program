//
//  cyclomatic_complexity.hpp
//  lexer
//
//  Created by Mohamed Raslan on 13/05/2024.
//

#ifndef cyclomatic_complexity_hpp
#define cyclomatic_complexity_hpp
#include <vector>
using namespace std;
vector<string> split(const string& str) ;
int getMcCabeMatricBycountingDecisionPoints(const string& code) ;
int calculateComplexityEdgesNodes(const string& code) ;
int calculateCyclomaticComplexityMcCabe(const string& code) ;


#endif /* cyclomatic_complexity_hpp */
