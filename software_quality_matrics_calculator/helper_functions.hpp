//
//  helper_functions.hpp
//  lexer
//
//  Created by Mohamed Raslan on 13/05/2024.
//

#ifndef helper_functions_hpp
#define helper_functions_hpp
#include<iostream>
#include<set>
#include<vector>
#include "halstead_caluculations.hpp"
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "function_to_print_token_type.hpp"
#include "lexer.hpp"
#include "lexer_regex.hpp"
#include <set>
#include<iomanip>


using namespace std;
void printList(vector<string> list);
void printSet(set<string> list);


void print_quality_matrics_report();

void extract_symbol_table_from_identifiers_list(vector<Token> identifiers);
void print_list_of_unique_identifiers();
string readSourceCode(const string& filename);
string getHardCoddedSourceCodeExample(int example_number);
void print_token_stream(vector<Token> token_stream);


void extract_token_stream_from_input_file(string source_code);
void extract_identifiers_from_token_stream(vector <Token> token_stream);
void print_list_of_unique_identifiers();

void export_symbol_table();
void export_token_stream();
void export_quality_matrics_report();
#endif /* helper_functions_hpp */
