//
//  halstead_caluculations.cpp
//  lexer
//
//  Created by Mohamed Raslan on 08/05/2024.
//

#include "halstead_caluculations.hpp"
#include <iostream>
#include <math.h>
using namespace std;

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

void getHalsteadMetric(int n1, int n2,int N1, int N2);
