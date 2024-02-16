#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

// Convert a string to upper case
string to_upper(string str);

// Remove leading and trailing spaces from string
string trim(string s);

// Prints instructions
void print_usage(char* argv0);

#endif // UTILS_H_