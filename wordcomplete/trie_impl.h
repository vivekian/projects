#pragma once 

#include <iostream> 
#include <memory> 
#include <vector> 

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
        void addWord(std::string word); 

        //! get all words for a common prefix 
        void getWordsForPrefix(std::string prefix, std::string curWord, std::vector<std::string>& words) const;

    private: 
        //! for the given vertex, explore the child trie to capture all words present 
        void depthFirstSearch(std::string curWord, std::vector<std::string>& words) const;

        //! is the vertex a word 
        bool isWord; 
        
        //! a vector of pointers to further vertices 
        std::vector<std::unique_ptr<Trie>> edges; 
}; 
