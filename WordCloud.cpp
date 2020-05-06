/*****************************************
** File:    WordCloud.cpp
** Project: CMSC 202 Project 5, Spring 2020
** Author:  Rooklyn Kline
** Date:    5/07/20
** Section: 02
** E-mail:  rkline2@umbc.edu
**
** This file involves inserting and manipulating a linked 
** list. The primary functions are to insert, and
** format a link list based on a given message from 
** a .txt file.
**
***********************************************/

#include "WordCloud.h"
#include <iostream>
using namespace std;

// WordCloud (Default Constructor)
    // Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud() {
    m_fileName = "";
    m_cloud = new LL<string>;
}

// WordCloud (Overloaded Constructor) 
    // Postconditions: Given a filename, returns
    // list of items and their frequency (stored in LL)
WordCloud::WordCloud(string filename) {
    m_fileName = filename;
    m_cloud = new LL<string>;
}

// ~WordCloud (Destructor)
    // Deallocates m_cloud
WordCloud::~WordCloud() { m_fileName.clear(); delete m_cloud; }

// LoadFile()
    // m_cloud is populated
void WordCloud::LoadFile() {
    ifstream file;
    file.open(m_fileName);
    string line = "";
    string word = "";
    while (getline(file, line)) {
        for (string::iterator curr_char = line.begin(); curr_char != line.end(); ++curr_char) {

            // creates a new word
            if (*curr_char != NEWWORD) {
                // lowercase each char 
                if (!ispunct(*curr_char)) {
                    *curr_char = tolower(*curr_char);
                }
                word += *curr_char;  
            }
            else {   
                RemovePunct(word);
                m_cloud->Insert(word);
                word = "";
            }
        }
        // last word in the line 
        if (word != "") {
            RemovePunct(word);
            m_cloud->Insert(word);
            word = "";
        }
        
    }
    file.close();
}

// RemovePunct 
    // Given a word (string), punctuation is removed from string
void WordCloud::RemovePunct(string& word) {
    int topIndex = word.length() - 1;
    int lowIndex = 0;
    char topChar = word[topIndex];
    char lowChar = word[lowIndex];
    
    // checks for punctuation

    // letters or numbers for topChar
    if (ispunct(topChar)) { word.erase(topIndex); }

    // letters or numbers for lowChar
    if (ispunct(lowChar)) { word.erase(lowIndex, lowIndex + 1); }

}

// RemoveCommon
    // Removes all common words after they are read
void WordCloud::RemoveCommon() {
    pair<string, int> curr_CloudVal;
    int currSize = m_cloud->GetSize();

    for (unsigned int i = 0; i < m_cloud->GetSize(); i++) {
        if (m_cloud->operator[](i).first != NOTFOUND) {
            curr_CloudVal = m_cloud->operator[](i);
            for (vector<string>::const_iterator excludeVal = EXCLUDE_LIST.begin(); excludeVal != EXCLUDE_LIST.end(); ++excludeVal) {
                if (curr_CloudVal.first == *excludeVal) {
                    m_cloud->RemoveAt(*excludeVal);
                    i--;
                }
            }
        }

    }

}

// RemoveSingles
   // Removes words with a frequency of 1 from m_cloud
void WordCloud::RemoveSingles() {
    LL<string>* curr = m_cloud;
    int numRemoved = 0;
    for (int i = 0; i < curr->GetSize(); i++) {
        if (m_cloud->operator[](i).first != NOTFOUND) {
            string key = curr->operator[](i).first;
            int freq = curr->operator[](i).second;
            if (freq == 1) {
                curr->RemoveAt(key);
                numRemoved++;
                i--;
            }
        }
    }
    cout << numRemoved << " words removed" << endl;
}

// Export
    // New export file is created with "data:frequency" one on each line
void WordCloud::Export() {
    string filename = "*.txt";
    cout << "What would you like to call the export file?" << endl;
    cin >> filename;

    ofstream newFile(filename);
    for (unsigned int i = 0; i != m_cloud->GetSize(); i++) {
        if (m_cloud->operator[](i).first != NOTFOUND) {
            newFile << m_cloud->operator[](i).first << SEPARATOR
                << m_cloud->operator[](i).second << NEWLINE;
        }
    }
    newFile.close();
    cout << "Output to exportFile: " << filename << endl;
    cout << m_cloud->GetSize() << " unique words exported" << endl;
}


// Start
    // Calls LoadFile, RemoveCommon, Diplay, and Export 
void WordCloud::Start() {
    string usrResponse = "";
    string lower_c_Response = "";
    LoadFile();
    RemoveCommon();
    while (usrResponse != SIN_YES && usrResponse != FULL_YES && usrResponse != SIN_NO && usrResponse != FULL_NO) {
        cout << "Would you like to remove all words with a frequency of 1? (\"y\", \"yes\", \"n\", \"no\")" << endl;
        cin >> usrResponse;

        // lowercase each char in the word
        for (string::iterator it = usrResponse.begin(); it != usrResponse.end(); ++it) {
            if (*it != NEWWORD) {
                if (!ispunct(*it)) {
                    *it = tolower(*it);
                }
                lower_c_Response += *it;
            }
        }
    }
    if (usrResponse == SIN_YES || usrResponse == FULL_YES) {
        RemoveSingles();
    }
    else {
        cout << "0 words removed" << endl;
    }
    cout << *m_cloud << endl;
    Export();
    
}

