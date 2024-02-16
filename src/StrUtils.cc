#include "StrUtils.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::unordered_map;

void print_usage(char* argv0) {
	cout << "Usage: " << argv0 << " \"<Text Here>\"" << endl;
}

string trim(string s) {
	size_t start = s.find_first_not_of(' ');

    if (start == string::npos) {
        return "";
    }

	size_t end = s.find_last_not_of(' ');
	
	return s.substr(start, end - start + 1);
}

string to_upper(string str) {
	for (auto & c: str) c = toupper(c);
	return str;
}