#ifndef OBJECTIVE_H_
#define OBJECTIVE_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

// Takes a vector of strings that concatenates to equal 
// target (ignoring spaces), and returns an int score of how well the "match".
// High scores are "better".
// 
// For example, if the space-separated words in target exactly
// match the components of candidate, one might say they match well.
// But if words in target are split across words in candidate, they
// don't match well.
int objective(vector<string> candidate, string target);

#endif