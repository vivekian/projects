#include "trie_impl.h"

void Trie::addWord(string word) 
{
    // if the word is empty then increment the word count  
    if (word.size() == 0) { 
        words++; 
    }
    else { 
        prefixes++; 
        char k = word[0]; 
        
        // create a new Trie object if one does not exist. 
        if (edges[k-'a'].get() == nullptr) { 
            edges[k-'a'].reset(new Trie());
        }
        
        // erase the first letter and recurse into the next vertex
        word.erase(0, 1); 
        edges[k-'a']->addWord(word); 
    }
}

uint32_t Trie::countWords(string word) const 
{ 
    char k = word[0]; 

    // if the word is empty, then query has been searched
    if (word.size() == 0) 
        return words; 
    else if (edges[k-'a'].get() == nullptr) { 
        return 0; 
    } 
    // remove the first char and recursively iterate again
    else { 
        word.erase(0, 1);  
        return edges[k-'a']->countWords(word); 
    }
}

uint32_t Trie::countPrefixes(string prefix) const 
{
   char k = prefix[0]; 
   
   if (prefix.size() == 0) 
       return words + prefixes; 
   else if (edges[k-'a'].get() == nullptr) { 
       return 0; 
   }
   else { 
       prefix.erase(0,1); 
       return edges[k-'a']->countPrefixes(prefix);
   }
}

void Trie::depthFirstSearch(string curWord, vector<string>& listWords) const 
{
   // if words is non-zero, that means current vertex is a word itself. 
   if (words) { 
      listWords.push_back(curWord); 
   }

   // iterate all 26 outgoing edges and if there are edges, then recursively iterate them as well. 
   for (char k=0; k<26; ++k) { 
      if (edges[k].get() != nullptr) {
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
    else if (edges[k-'a'].get() == nullptr) {
        return; 
    }
    else { 
        prefix.erase(0,1); 
        return edges[k-'a']->getWordsForPrefix(prefix, curWord+k, listWords);
    }
} 
