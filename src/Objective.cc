#include "Objective.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

#define START_SCORE 1000

int objective(vector<string> candidate, string target) {
    int score = START_SCORE;
    
    size_t i = 0;
    for (auto& word : candidate) {
        if (word == " ") {
            continue;
        }
        i += word.size();
        if (i < target.size() && target[i] != ' ') {
            score--;
        }
    }

    return score - candidate.size();
}