#pragma once 

#include <iostream> 
#include <memory> 
#include <vector> 

using namespace std; 

namespace { 
    const uint32_t NUM_ALPHABETS = 26; 
}

//! Tree like data structure for quick retrieval of words based on common prefix. 
class Trie 
{
    public:  
        //! constructor - setup all the edges to be nullptr. 
        Trie(): isWord(false)
        {
            for (int i=0; i<NUM_ALPHABETS; ++i) { 
                edges.push_back(nullptr);
            }
        }

        //! empty destructor 
        ~Trie() {} 

        //! add a word to the trie starting from the root of the tree.
        void addWord(string word); 

        //! get all words for a common prefix 
        void getWordsForPrefix(string prefix, string curWord, vector<string>& words) const;

    private: 
        //! for the given vertex, explore the child trie to capture all words present 
        void depthFirstSearch(string curWord, vector<string>& words) const;

        //! is the vertex a word 
        bool isWord; 
        
        //! a vector of pointers to further vertices 
        vector<unique_ptr<Trie>> edges; 
}; 
