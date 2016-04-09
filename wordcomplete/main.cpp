#include <fstream> 
#include <string> 
#include <sys/stat.h>

#include "trie_impl.h" 

using namespace std; 

namespace { 
    bool fileExists(const string& filename) 
    { 
        struct stat buffer;   
        return (stat (filename.c_str(), &buffer) == 0); 
    }

    void FillWordsInTrie(const string & filename, Trie& trie)
    {
        if (!fileExists(filename)) 
            throw string("file does not exist"); 

        ifstream infile(filename);  
        string word; 

        while (infile >> word) { 
            trie.addWord(word); 
        }
    } 

    void usage() 
    { 
        cerr << "./wordcomplete <prefix>" << endl; 
    }
}

int main(int argc, char* argv[]) 
{ 
    if (argc < 2 || (!strcmp("-h", argv[1]))) { 
        usage(); 
        return 1; 
    }    

    Trie root; 
    string prefix = string(argv[1]);     

    try { 
        cout << "building word list, please wait .." << endl; 

        // read in the 10000 most common english words into the Trie struct    
        FillWordsInTrie("dict_words.txt", root); 

        vector<string> listWords; 
        root.getWordsForPrefix(prefix, string(""), listWords);

        if (listWords.size() == 0) 
            cerr << "no words found for " << prefix << endl; 

        for (auto word: listWords) 
            cout << word << endl; 
    } 
    catch (string err) { 
        cerr << err << endl; 
        return 1; 
    } 

    return 0; 
}
