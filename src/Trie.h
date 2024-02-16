#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
using std::hash;

// Class representing prefix tree
// https://en.wikipedia.org/wiki/Trie
class Trie {
    public:
        Trie();
        ~Trie();

        // Adds a string to the trie
        void add(string s);

        // Returns a vector where element is a string that 
        // concatenate to equal target and that were previously added to the trie
        vector<string> search(string target);

    private:

        // Represents a single trie node
        struct _Node {
            bool present;
            unordered_map<char, _Node*> children;
        };

        // Allows hashing of custom key type in cache
        struct pair_hash {
            template <class T1, class T2>
            size_t operator() (const pair<T1,T2> &p) const {
                auto h1 = hash<T1>{}(p.first);
                auto h2 = hash<T2>{}(p.second);
                return h1 ^ h2;  
            }
        };

        _Node* _root;
        unordered_map<pair<_Node*, string>, vector<string>, pair_hash> _cache;

        // Same as public search, but starting from node. 
        // Path is characters traveresed to arrive at node
        vector<string> search(string target, _Node* root, string path);

        // Delete a node and all children nodes,
        // recursively
        static void del(_Node* root);
};

#endif // TRIE_H_
