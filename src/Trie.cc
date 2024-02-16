// William Galvin, 2023

#include "Trie.h"
#include "StrUtils.h"
#include "Objective.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::min_element;

Trie::Trie() {
    this->_root = new _Node();
}

Trie::~Trie() {
    del(this->_root);
}

void Trie::add(string s) {
    s = to_upper(s);
    _Node* cur = this->_root;
    for (auto& c : s) {
        if (!cur->children.count(c)) {
            cur->children[c] = new _Node();
        }
        cur = cur->children[c];
    }
    cur->present = true;
}

vector<string> Trie::search(string target, _Node* root, string path) {
    auto key = make_pair(root, target);
    if (this->_cache.count(key)) {
        return this->_cache[key];
    }

    vector<string> results;
    vector<vector<string>> options;

    if (target.length() == 0) {
        if (root->present) {
            results.push_back({path});
        }
        this->_cache[key] = results;
        return results;
    }

    if (root->children.count(target[0])) {
        string next_target = target.substr(1, target.length());
        vector<string> next_result = search(next_target, root->children[target[0]], path + target[0]);
        if (!next_result.empty()) {
            options.push_back(next_result);
        }
    }

    if (root->present && root != this->_root) {
        vector<string> v = search(target, this->_root, "");
        v.insert(v.begin(), path);
        options.push_back(v);
    }

    if (options.empty()) {
        return {};
    }

    results = *min_element(options.begin(), options.end(), [target](vector<string> u, vector<string> v) {
        return objective(u, target) > objective(v, target);
    });
    this->_cache[key] = results;
    return results;
}

vector<string> Trie::search(string target) {
    return this->search(to_upper(target), this->_root, "");
}

void Trie::del(_Node* root) {
    for (auto const& [_, child] : root->children) {
		del(child);
	}
    delete root;
}
