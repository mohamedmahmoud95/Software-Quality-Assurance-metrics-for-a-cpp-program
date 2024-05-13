//
//  halstead_caluculations.hpp
//  lexer
//
//  Created by Mohamed Raslan on 08/05/2024.
//

#ifndef halstead_caluculations_hpp
#define halstead_caluculations_hpp

#include <stdio.h>

// prototyping

void countNumberOfOperator( std::string input);

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

#endif /* halstead_caluculations_hpp */
