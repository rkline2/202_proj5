#include "WordCloud.h"
#include <iostream>
using namespace std;

// Name: WordCloud (Default Constructor)
    // Desc: Used to pass an essay (in input file) and generates word list and frequency
    //       Dynamically allocates m_cloud. m_fileName would be hardcoded.
    // Preconditions: Input file has correctly formatted input
    // Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud() {
    m_fileName = "";
    m_cloud = new LL<string>;
}

// Name: WordCloud (Overloaded Constructor) - Passed filename for input
    // Desc: Used to pass an essay (in input file) and generates word list and frequency
    //       Dynamically allocates m_cloud
    // Preconditions: Input file has correctly formatted input
    // Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud(string filename) {
    m_fileName = filename;
    m_cloud = new LL<string>;
}

// Name: ~WordCloud (Destructor)
    // Desc: Deallocates m_cloud
    // Preconditions: m_cloud has been dynamically allocated
    // Postconditions: m_cloud is empty
WordCloud::~WordCloud() { delete m_cloud; }

// Name: LoadFile()
    // Desc: Loads a file (everything as a string although could be anything stringlike)
    //       Each input file is an unknown length
    // Preconditions: m_fileName is populated with good data
    // Postconditions: m_cloud is populated
void WordCloud::LoadFile() {
    ifstream file;
    file.open(m_fileName);
    string word;
    while (getline(file, word, ' ')) {
        if (word != "\n") {
            cout << word << endl;
        }
        

    }
    file.close();
}

// Name: RemovePunct (passed a string
    // Desc: When passed a string, removes all non letter punctation on the beginning
    //       or end of the string.
    //       These are all ok: "don't" "inner-circle" but "candy," is bad
    //       Is called during LoadFile
    // Preconditions: Strings to be evaluated
    // Postconditions: Punctuation is removed from string
void WordCloud::RemovePunct(string&) {}

// Name: RemoveCommon
    // Desc: Iterates through m_cloud and removes all common words after they are read
    // Preconditions: m_cloud is populated and EXCLUDE_LIST is populated
    // Postconditions: m_cloud will have no words from EXCLUDE_LIST
void WordCloud::RemoveCommon() {}

// Name: RemoveSingles
   // Desc: Asks the user if they would like to remove words with a frequency of 1
   //       Should use the overloaded [] NOTE: Don't forget m_cloud is a pointer!
   // Preconditions: m_cloud is populated
   // Postconditions: m_cloud will have no words with a frequency of 1
void WordCloud::RemoveSingles() {}

// Name: Export
    // Desc: Iterates through m_cloud and exports to file "data:frequency"
    // Preconditions: m_cloud is populated
    // Postconditions: New export file is created with "data:frequency" one on each line
void WordCloud::Export() {}

// Name: Start
    // Desc: Calls LoadFile, RemoveCommon, Diplay, and Export 
    // Preconditions: None (filename is available)
    // Postconditions: None
void WordCloud::Start() {
    LoadFile();
}

/*
string m_fileName; //Name of the input file
    LL<string>* m_cloud; //LL to store all data
*/
