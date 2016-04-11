#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "trie_impl.h"

using namespace std;

namespace {
    const string DICT_NAME = "/usr/share/dict/words";

    //! stat is the fastest way to determine if a file exists
    bool fileExists(const string& filename)
    {
        struct stat buffer;
        return (stat (filename.c_str(), &buffer) == 0);
    }

    //! read the text file, assuming one word per line
    //! fill the trie data structure with all the words
    //! time complexity O(mn) where m is number of words
    //! and n is avg length of word to be filled
    void FillWordsInTrie(const string & filename, Trie& trie)
    {
        if (!fileExists(filename))
            throw string("file does not exist " + filename);

        ifstream infile(filename);
        string word;

        while (infile >> word) {
            // convert each word to lowercase and then add it to the trie
	        transform(word.begin(), word.end(), word.begin(), ::tolower);

	    // if a word has non alpha chars then skip it.
	    if (word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == string::npos) {
        	    trie.addWord(word);
	        }
        }
    }

    void usage()
    {
        cerr << "./wordcomplete <prefix>" << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2 || (!strncmp("-h", argv[1], 4))) {
        usage();
        return 1;
    }

    Trie root;
    string prefix = string(argv[1]);

    try {
        cout << "building word list, please wait .." << endl;

        // common file found on Unix based systems with all english words
        FillWordsInTrie(DICT_NAME, root);

        vector<string> listWords;
        root.getWordsForPrefix(prefix, string(""), listWords);

        if (listWords.size() == 0) {
            cerr << "no words found for " << prefix << endl;
            return 1;
        }

        for (auto word: listWords)
            cout << word << endl;
    }
    catch (string err) {
        cerr << err << endl;
        return 1;
    }

    return 0;
}
