#pragma once 

#include <iostream> 
#include <memory> 
#include <vector> 

using namespace std; 

// Tree like data structure for quick retrieval of words based on common prefix. 
class Trie 
{
    public:  
        // constructor - setup all the edges to be nullptr. 
        Trie():words(0), prefixes(0)
        {
            for (int i=0; i<26; ++i) 
                edges.push_back(nullptr);
        }

        ~Trie() {} 

        // add a word to the trie based on root of the tree. 
        void addWord(string word); 

        // count the number of words+prefixes for a common prefix
        uint32_t countPrefixes(string prefix) const; 
        uint32_t countWords(string word) const; 

        // get all words for a common prefix 
        void getWordsForPrefix(string prefix, string curWord, vector<string>& words) const;

    private: 
        // from the vertex, explore the entire trie to capture all words present 
        void depthFirstSearch(string curWord, vector<string>& words) const;
        // number of words from the root.  
        uint32_t words; 
        // number of common prefixes. 
        uint32_t prefixes; 
        // a vector of pointers to further vertexes 
        vector<unique_ptr<Trie> > edges; 
}; 
