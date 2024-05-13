#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "function_to_print_token_type.hpp"
#include "lexer.hpp"
#include "lexer_regex.hpp"
#include <set>
#include "halstead_caluculations.hpp"
#include "cyclomatic_complexity.hpp"
#include "helper_functions.hpp"
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stack>


using namespace std;



int n1 = 0 ; //No. of distinct opreators
int N1 = 0 ; //total No. of opreators
int n2 = 0 ; //No. of distinct operands
int N2 = 0 ; //total No. of operands

vector<string> operands;
set<string> distinctOperands;
vector <Token> identifiers;
set<Token> listOfUniqeIdentifiers;
vector<Token> token_stream;
vector<Token> symbol_table; //table of unique identifiers, and yes, it's the same as listOfUniqeIdentifiers
vector<string> split(const string& str) ;
int getMcCabeMatricBycountingDecisionPoints(const string& code) ;
int calculateComplexityEdgesNodes(const string& code) ;
int calculateCyclomaticComplexityMcCabe(const string& code) ;


int predicate_complexity = 0;
int McCabe_complexity = 0;
// File to read the source code from
//If it says: "Error opening file: ", you probably need to change the path to the path where the file exists on your machine
string sourse_code_file_name_and_path = "/Users/mohamedraslan/xcode projects/lexer_xcode_version_27march2024/software_quality_matrics_calculator/code_example4.txt";
//there are 5 code examples

string quality_matrics_report_file_name_and_path = "/Users/mohamedraslan/xcode projects/lexer_xcode_version_27march2024/software_quality_matrics_calculator/quality_matrics_report.txt";


string token_stream_output_file_name_and_path = "/Users/mohamedraslan/xcode projects/lexer_xcode_version_27march2024/software_quality_matrics_calculator/token_stream.txt";

string symbol_table_output_file_name_and_path = "/Users/mohamedraslan/xcode projects/lexer_xcode_version_27march2024/software_quality_matrics_calculator/symbol_table.txt";



int main() {
    
    // Sample source code string
    std::string  source_code = readSourceCode(sourse_code_file_name_and_path);
    //or use:
    //std::string input = getHardCoddedSourceCodeExample(3);

    predicate_complexity = calculateCyclomaticComplexityMcCabe(source_code);
    McCabe_complexity = calculateCyclomaticComplexityMcCabe(source_code);
    print_quality_matrics_report();
    Lexer lexer(source_code);
    Token token;
    extract_token_stream_from_input_file(source_code);
    extract_identifiers_from_token_stream(token_stream);
    extract_symbol_table_from_identifiers_list(identifiers);

    countNumberOfOperator(source_code);
    
    getHalsteadMetric( n1,  n2, N1,  N2);

    print_token_stream(token_stream);
    print_list_of_unique_identifiers();
    
    export_quality_matrics_report();
    return 0;
}







//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//Halstead metrics functions
float getEstimatedLength(int n1, int n2){
    return n1*log(n1) + n2*log(n2);
}

float getPurityRatio(int n1, int n2,int N1, int N2){
    return  getEstimatedLength(n1,n2) /getProgramLength(N1, N2) ;
}

float getVolume(int n1,int n2){
    return getEstimatedLength(n1,n2)*log(getProgramVocabulary(n1,n2));
}

float getDifficulty(int n1,int n2, int N2){
    return (n1/2)*(N2/n2);
}

float getEffort(int n1,int n2,int N2){
    return getDifficulty(n1,n2,N2) * getVolume(n1,n2);
}
float getNumberOfBugs_Volume(int n1, int n2){
    return getVolume(n1,n2)/3000;
}
float getNumberOfBugs_Effort(int n1, int n2,int N2){
   return pow(getEffort(n1,n2,N2),(2/3))/3000;
}
int getProgramLength(int N1, int N2){
    return  N1+N2;
}
int getProgramVocabulary(int n1, int n2){
    return  n1+n2;
}

void getHalsteadMetric(int n1, int n2,int N1, int N2){
    cout<<endl<<endl;
    cout<<"Halstead complexity matrics:"<<endl;
    cout<<"  - Program length: "<< getProgramLength(N1,N2) <<endl;
    cout<<"  - Program vocabulary: "<< getProgramVocabulary(n1,n2) <<endl;
    cout<<"  - Estimated length: "<< getEstimatedLength(n1,n2) <<endl;
    cout<<"  - Purity Ratio: "    << getPurityRatio (n1, n2, N1, N2) <<endl;
    cout<<"  - Volume: "<< getVolume(n1,n2) <<endl;
    cout<<"  - Difficulty: "<< getDifficulty( n1, n2,  N2) <<endl;
    cout<<"  - Effort: "<< getEffort( n1, n2, N2) <<endl;
    cout<<"  - Number of bugs from volume: "<< getNumberOfBugs_Volume(n1,n2) <<endl;
    cout<<"  - Number of bugs from effort: "<< getNumberOfBugs_Effort(n1,n2, N2) <<endl;
    cout<< endl <<endl;
}



void countNumberOfOperator( std::string input){
    cout<<endl<<"Calculating Halstead complexity matrics...\n";
    std::vector <std::string> operators;
    
    Lexer lexer(input);
    Token token;
    
    do {
        
        token = lexer.getNextToken();
        if (LexerRegex::matchOperator(token.lexeme)) {
            operators.push_back(token.lexeme) ;
        }
    
        for (int i = 0 ; i < token.lexeme.size(); i++){
            if (isdigit(token.lexeme[i]) == false)
            {
                continue;
            }
            else
            {
                operands.push_back(token.lexeme);
            }
        }
        
        //check if lexeme is in identifier
        if (((isalpha(token.lexeme[0]))||(token.lexeme[0] == '_'))
            &&
            (( LexerRegex::matchKeyword(token.lexeme)  == false)
            &&
             (LexerRegex::matchDatatype(token.lexeme)  == false))  )
        {
            operands.push_back(token.lexeme);
       }
            
    } while (token.lexeme != "");
    
    std::set<std::string> listOfDistinctOperators;

       // Insert elements from the vector into the set (duplicates will be automatically removed)
    for (int i = 0 ; i < operators.size() ; i++)
    {
        listOfDistinctOperators.insert(operators[i]);
    }
 
        std::cout<<"\n\n============================\n";

    std::cout<<"printing the list of operators:\n";
    printList(operators);
    std::cout<<"\n============================\n";

    
    
    std::cout<<"\nprinting the list of distinct operators:\n";
    printSet(listOfDistinctOperators);
    std::cout<<"\n============================\n";

    
    n1 = listOfDistinctOperators.size();
    N1 = operators.size();

    
    std::cout<<"\n n1 = " <<n1<<std::endl;
    std::cout<<" N1 = " <<N1<<std::endl;
    
    
    std::cout<<"\n============================\n";

std::cout<<"printing the list of operands:\n\n";
printList(operands);
std::cout<<"\n============================\n";

    for (int i = 0 ; i < operands.size() ; i++)
    {
        distinctOperands.insert(operands[i]);
    }
std::cout<<"\nprinting the list of distinct operands:\n";
printSet(distinctOperands);
std::cout<<"\n============================\n";


n2 = distinctOperands.size();
N2 = operands.size();


std::cout<<"\n n2 = " <<n2<<std::endl;
std::cout<<" N2 = " <<N2<<std::endl;

}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//













//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//Cyclomatic Complexity matrics functions:


// Function to split a string into tokens (words)
vector<string> split(const string& str) {
  vector<string> tokens;
  string token;
  for (char ch : str) {
    if (isalnum(ch) || ch == '_') {
      token += ch;
    } else if (!token.empty()) {
      tokens.push_back(token);
      token.clear();
    }
  }
  if (!token.empty()) {
    tokens.push_back(token);
  }
  return tokens;
}

// Function to count decision points (predicates)
int getMcCabeMatricBycountingDecisionPoints(const string& code) {
  static const unordered_set<string> keywords = {"if", "else", "switch", "case", "while", "for"};
  int decisionPoints = 0;
  for (const string& line : split(code)) {
    for (const string& keyword : keywords) {
      if (line.find(keyword) != string::npos) {
        decisionPoints++;
        break; // Only count the first occurrence per line
      }
    }
  }
  return decisionPoints;
}


// Function to calculate cyclomatic complexity using McCabe's method (same as before)
int calculateCyclomaticComplexityMcCabe(const string& code) {
  return getMcCabeMatricBycountingDecisionPoints(code) + 1;
}


// Function to calculate cyclomatic complexity using Edges-Nodes method
int calculateComplexityEdgesNodes(const string& code) {
  // 1. Preprocess code (remove comments, whitespaces)
  string preprocessedCode;
  for (char ch : code) {
    if (isalnum(ch) || ch == '_' || ch == '.' || ch == '{') {
      preprocessedCode += ch;
    }
  }

  // 2. Count basic blocks (sequences without branches)
  int basicBlocks = 0;
  bool inBlock = false;
  for (char ch : preprocessedCode) {
    if (ch == '{') {
      inBlock = true;
    } else if (ch == '}') {
      if (inBlock) {
        basicBlocks++;
      }
      inBlock = false;
    } else if (!isalnum(ch) && !inBlock) {
      basicBlocks++; // Assuming basic block ends with a non-alphanumeric outside curly braces
    }
  }

  // 3. Estimate edges based on control flow keywords and nesting levels
  int edges = 0;
  int nestingLevel = 0;
  for (char ch : preprocessedCode) {
    if (ch == '{') {
      nestingLevel++;
    } else if (ch == '}') {
      nestingLevel--;
    } else if (iscntrl(ch)) { // Control characters (including newline)
      edges += nestingLevel + 2; // Add 2 for potential entry/exit edges
    }
  }


  // 4. Estimate nodes based on basic blocks and nesting levels
  int nodes = basicBlocks + nestingLevel + 1; // Add 1 for starting node

  // 5. Calculate cyclomatic complexity
    return edges - nodes + 2;
}



//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//















//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//Helper functions
void printList(std::vector<std::string> list)
{
    for (int i = 0 ; i < list.size(); i++)
    {
        std::cout<<list[i]<<"\t";
    }
}


void printSet(std::set<std::string> list)
{
    for (const std::string& str : list) {
         std::cout << str << " ";
     }
}



// Function to read source code from a file into a string
string readSourceCode(const string& filename) {
    ifstream inputFile(filename);

    // Error handling: Check if the file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
               exit(1);
    }

    // Read the entire file content into a string
    string inputString;
    getline(inputFile, inputString, static_cast<char>(EOF));
    
    inputFile.close();
    
    return inputString;
}

string getHardCoddedSourceCodeExample(int example_number){
    if (example_number == 1){
        return "bool private public protected class template :: 3.14e5 if x == y return 1; else return 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; [] [ ]  float zrka23elyamama zrka23elyamama zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" & | ^ ~";
    }
    else if (example_number == 2)
    {
        return " void extract_symbol_table_from_identifiers_list(vector<Token> identifiers){for (int i = 0 ; i < identifiers.size ; i++) { symbole_table.push_back(identifiers[i]);}}";
    }
    
    else if (example_number == 3)
    {
        return "int i = 0; class Token { string lexeme; TokenType type; void print(string source_code){ for(int i = 0 ; i < source_code.size; i++){ cout<<source_code[i]<<endl;} cout<<\"out\";";
    }
    else{
        return "bool private public protected class template :: 3.14e5 if x == y return 1; else return 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; [] [ ]  float zrka23elyamama zrka23elyamama zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" & | ^ ~";
    }
}


void extract_symbol_table_from_identifiers_list(vector<Token> identifiers){
    // Insert elements from the vector into the set (duplicates will be automatically removed)
    for (int i = 0 ; i < identifiers.size() ; i++)
    {
        symbol_table.push_back(identifiers[i]);
    }
}

void print_token_stream(vector<Token> token_stream){
    cout<<"\n\n================================================\n";
    cout<<"printing token stream:\n";
    for (const Token& token : token_stream) {
        cout <<  "Token: " <<setw(10) << left << token.lexeme << setw(10) << right << "Type: " <<tokenTypeNames[token.type]<< endl;
    }
    cout<<"\n\n================================================\n";

}

void print_list_of_unique_identifiers(){
    cout<<"\n\n================================================\n";
    cout<<"printing list of unique identifiers:\n";
    for (const Token& identifier : symbol_table) {
      cout << identifier.lexeme << endl;
    }
    cout<<"================================================\n";
}


void export_token_stream(string token_stream_output_file_name_and_path){
    ofstream tokenStreamFile(token_stream_output_file_name_and_path);
    for (const Token& token : token_stream) {
        tokenStreamFile << "Token: " <<setw(10) << left << token.lexeme << setw(10) << right << "Type: " <<tokenTypeNames[token.type]<< endl;
    }
    tokenStreamFile.close();
}

void export_symbol_table(string symbol_table_output_file_name_and_path){
    ofstream symbolTableFile(symbol_table_output_file_name_and_path);
    for (const Token& identifier : symbol_table) {
        symbolTableFile << identifier.lexeme << endl;
    }
    symbolTableFile.close();
}



void extract_token_stream_from_input_file(string source_code)
{
    Token token;
    Lexer lexer(source_code);
    do {
        token = lexer.getNextToken();
        token_stream.push_back(token);
    } while (token.lexeme != "");

//    return token_stream;
}

void extract_identifiers_from_token_stream(vector <Token> token_stream){
    for (const Token& token : token_stream)
        {
            if((isalpha(token.lexeme[0]) || token.lexeme[0] == '_')){
                identifiers.push_back(token);
            }
        }
    }

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//





//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
void print_quality_matrics_report(){
    cout<<"Cyclomatic Complexity matrics: \n"<<endl;
    cout << "  - using Predicate Method: " << predicate_complexity  << endl;
    cout << "  - using McCabe's Method: " << McCabe_complexity << endl;
    cout<<endl<<endl;
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//






//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

void export_quality_matrics_report(){
    ofstream report_file (quality_matrics_report_file_name_and_path);
    report_file<<"Quality matrics report:\n"<<endl;
    report_file<<"\n//==================================//\n";
    report_file<<"Halstead matrics: "<<endl;

    report_file<<"Program length: "<< getProgramLength(N1,N2) <<endl;
    report_file<<"Program vocabulary: "<< getProgramVocabulary(n1,n2) <<endl;
    report_file<<"Estimated length: "<< getEstimatedLength(n1,n2) <<endl;
    report_file<<"Purity Ratio: "    << getPurityRatio (n1, n2, N1, N2) <<endl;
    report_file<<"Volume: "<< getVolume(n1,n2) <<endl;
    report_file<<"Difficulty: "<< getDifficulty( n1, n2,  N2) <<endl;
    report_file<<"Effort: "<< getEffort( n1, n2, N2) <<endl;
    report_file<<"Number of bugs from volume: "<< getNumberOfBugs_Volume(n1,n2) <<endl;
    report_file<<"Number of bugs from effort: "<< getNumberOfBugs_Effort(n1,n2, N2) <<endl;
    report_file<<"\n//==================================//\n";

    report_file<<"\n\n"<<endl;
    report_file<<"\n//==================================//\n";
    report_file<<"Cyclomatic Complexity matrics: \n"<<endl;
    report_file << "  - using Predicate Method: " << predicate_complexity  << endl;
    report_file << "  - using McCabe's Method: " << McCabe_complexity << endl;
    report_file<<"\n//==================================//\n";


    report_file.close();
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
