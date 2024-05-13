//
//  cyclomatic_complexity.cpp
//  lexer
//
//  Created by Mohamed Raslan on 13/05/2024.
//

#include "cyclomatic_complexity.hpp"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


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
int countDecisionPoints(const string& code, vector<string> ) {
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


// Function to calculate cyclomatic complexity using McCabe's method (same as before)
int calculateCyclomaticComplexityMcCabe(const string& code) {
  return countDecisionPoints(code) + 1;
}

