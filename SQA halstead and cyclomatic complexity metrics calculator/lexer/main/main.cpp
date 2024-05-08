#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "function_to_print_token_type.hpp"
#include "lexer.hpp"
#include "lexer_regex.hpp"
#include <set>
#include "halstead_caluculations.hpp"
using namespace std;



// prototyping
float getEstimatedLength(int n1, int n2);
float getPurityRatio(int n1, int n2,int N1, int N2);
float getVolume(int n1,int n2);
float getDifficulty(int n1,int n2, int N2);
float getEffort(int n1,int n2,int N2);
float getNumberOfBugs_Volume(int n1, int n2);
float getNumberOfBugs_Effort(int n1, int n2,int N2);
int  getProgramLength(int N1, int N2);
int getProgramVocabulary(int n1, int n2);

void getHalsteadMetric(int n1, int n2,int N1, int N2);
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
    cout<<"Program length: "<< getProgramLength(N1,N2) <<endl;
    cout<<"Program vocabulary: "<< getProgramVocabulary(n1,n2) <<endl;
    cout<<"Estimated length: "<< getEstimatedLength(n1,n2) <<endl;
    cout<<"Purity Ratio: "    << getPurityRatio (n1, n2, N1, N2) <<endl;
    cout<<"Volume: "<< getVolume(n1,n2) <<endl;
    cout<<"Difficulty: "<< getDifficulty( n1, n2,  N2) <<endl;
    cout<<"Effort: "<< getEffort( n1, n2, N2) <<endl;
    cout<<"Number of bugs from volume: "<< getNumberOfBugs_Volume(n1,n2) <<endl;
    cout<<"Number of bugs from effort: "<< getNumberOfBugs_Effort(n1,n2, N2) <<endl;
    cout<< endl <<endl;

}


int n1 = 0 ; //No. of distinct opreators
int N1 = 0 ; //total No. of opreators
int n2 = 0 ; //No. of distinct operands
int N2 = 0 ; //total No. of operands

vector<string> operands;
set<string> distinctOperands;


void removeDuplicates(std::string listOfOperators [], std::string* listOfDistinctOperators)
{
    int currentIndex = 0;
    for (int i = 0 ; i < listOfOperators->size() ; i++ )
    {
        for (int j = i+1 ; j < listOfOperators->size() ; j++)
        {
            if (listOfOperators[i] == listOfOperators[j] )
            {
                continue;
            } else {
                listOfDistinctOperators[currentIndex] = listOfOperators[i];
                currentIndex++;
            }
        }
    }
}


void printList(std::vector<std::string> list)
{
    for (int i = 0 ; i < list.size(); i++)
    {
        std::cout<<std::endl<<list[i];
    }
}


void printSet(std::set<std::string> list)
{
    for (const std::string& str : list) {
         std::cout << str << " ";
     }
}

void countNumberOfOperator( std::string input){
    std::vector <std::string> operators;
    
    Lexer lexer(input);
    Token token;
    
    do {
        
        token = lexer.getNextToken();
        std::cout << "Token: " << token.lexeme << ", Type: ";
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
 
        std::cout<<"\n\n============================\n\n";

    std::cout<<"printing the list of operators:\n\n";
    printList(operators);
    std::cout<<"\n\n============================\n\n";

    
    
    std::cout<<"\n\n\nprinting the list of distinct operators:\n\n";
    printSet(listOfDistinctOperators);
    std::cout<<"\n\n============================n\n";

    
    n1 = listOfDistinctOperators.size();
    N1 = operators.size();

    
    std::cout<<"\n\n n1 = " <<n1<<std::endl;
    std::cout<<"\n\n N1 = " <<N1<<std::endl;
    
    
    
    
    
    
    std::cout<<"\n\n============================\n\n";

std::cout<<"printing the list of operands:\n\n";
printList(operands);
std::cout<<"\n\n============================\n\n";

    for (int i = 0 ; i < operands.size() ; i++)
    {
        distinctOperands.insert(operands[i]);
    }
std::cout<<"\n\n\nprinting the list of distinct operands:\n\n";
printSet(distinctOperands);
std::cout<<"\n\n============================n\n";


n2 = distinctOperands.size();
N2 = operands.size();


std::cout<<"\n\n n2 = " <<n2<<std::endl;
std::cout<<"\n\n N2 = " <<N2<<std::endl;

}



int main() {
    // Sample input string
    std::string input = "  //This is a comment\n  commentsAreNeglected  /*and\nthis\n a\nmulti-line\ncomment*/  3.14e5if x == y return 1; string else if else if  for for for return 0; while _cycle = 9; int frawla = 2098 ; x x x x y Donia int = --8++ ; [] [ ]  float zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" & | ^ ~";

    Lexer lexer(input);
    Token token;

    do {
        token = lexer.getNextToken();
        std::cout << "Token: " << token.lexeme << ", Type: ";
        printTokenType(token);
    } while (token.lexeme != "");
    
    countNumberOfOperator(input);
    
    getHalsteadMetric( n1,  n2, N1,  N2);

    return 0;
}


