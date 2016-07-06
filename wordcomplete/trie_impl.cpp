#include "trie_impl.h"

using std::string; 
using std::vector; 
using std::unique_ptr; 

void Trie::addWord(string word) 
{
    // if the word is empty then increment the word count  
    if (word.size() == 0) { 
        isWord = true; 
    }
    else { 
        char k = word[0]; 
        
        // create a new Trie object if one does not exist. 
        if (edges[k-'a'] == nullptr) { 
            edges[k-'a'].reset(new Trie());
        }
        
        // erase the first letter and recurse into the next vertex
        word.erase(0, 1); 
        edges[k-'a']->addWord(word); 
    }
}

void Trie::depthFirstSearch(string curWord, vector<string>& listWords) const 
{
   // if words is non-zero, that means current vertex is a word itself. 
   if (isWord) { 
      listWords.push_back(curWord); 
   }

   // iterate all 26 outgoing edges and if there are edges, then recursively iterate them as well. 
   for (char k=0; k<NUM_ALPHABETS; ++k) { 
      if (edges[k] != nullptr) {
         char nextChar = 'a' + k; 
         edges[k]->depthFirstSearch(curWord + nextChar, listWords); 
      }
   } 
} 

void Trie::getWordsForPrefix(string prefix, string curWord, vector<string>& listWords) const 
{ 
    char k = prefix[0]; 

    if (prefix.size() == 0) {
        return depthFirstSearch(curWord, listWords); 
    }
    else if (edges[k-'a'] == nullptr) {
        return; 
    }
    else { 
        prefix.erase(0,1); 
        return edges[k-'a']->getWordsForPrefix(prefix, curWord+k, listWords);
    }
} 
