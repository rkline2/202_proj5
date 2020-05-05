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
WordCloud::~WordCloud() { m_fileName.clear(); delete m_cloud; }

// Name: LoadFile()
    // Desc: Loads a file (everything as a string although could be anything stringlike)
    //       Each input file is an unknown length
    // Preconditions: m_fileName is populated with good data
    // Postconditions: m_cloud is populated
void WordCloud::LoadFile() {
    ifstream file;
    file.open(m_fileName);
    string line = "";
    string word = "";
    while (getline(file, line)) {
        for (string::iterator curr_char = line.begin(); curr_char != line.end(); ++curr_char) {
            if (*curr_char != ' ') {
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

// Name: RemovePunct (passed a string
    // Desc: When passed a string, removes all non letter punctation on the beginning
    //       or end of the string.
    //       These are all ok: "don't" "inner-circle" but "candy," is bad
    //       Is called during LoadFile
    // Preconditions: Strings to be evaluated
    // Postconditions: Punctuation is removed from string
void WordCloud::RemovePunct(string& word) {
    int topIndex = word.length() - 1;
    int lowIndex = 0;
    char topChar = word[topIndex];
    char lowChar = word[lowIndex];
    
    /*
    while (!isLower) {
        topChar = word[topIndex];
        lowChar = word[lowIndex];

        if ((topChar <= MAX_UP_C_VAL) && (topChar >= MIN_UP_C_VAL)) {
            topChar = tolower(topChar);
        }

        if ((lowChar <= MAX_UP_C_VAL) && (lowChar >= MIN_UP_C_VAL)) {
            topChar = tolower(topChar);
        }
        // stops when the two chars reach the middle of the word
        if ((topIndex == lowIndex) || (lowIndex == midIndex)) {
            topIndex = word.length() - 1;
            lowIndex = 0;
            topChar = word[topIndex];
            lowChar = word[lowIndex];
            isLower = true;
        }
        else {
            topIndex--;
            lowIndex++;
        }

    }
    */

    // checks for punctuation

    // letters or numbers for topChar
    if (ispunct(topChar)) { word.erase(topIndex); }

    // letters or numbers for lowChar
    if (ispunct(lowChar)) { word.erase(lowIndex, lowIndex + 1); }

}

// Name: RemoveCommon
    // Desc: Iterates through m_cloud and removes all common words after they are read
    // Preconditions: m_cloud is populated and EXCLUDE_LIST is populated
    // Postconditions: m_cloud will have no words from EXCLUDE_LIST
void WordCloud::RemoveCommon() {
    pair<string, int> curr_CloudVal;
    /*
    string curr_ExcludeVal;
    int low;
    int high;
    int mid;
    bool isFound;
    */
    int currSize = m_cloud->GetSize();
    for (unsigned int i = 0; i < m_cloud->GetSize(); i++) {
        curr_CloudVal = m_cloud->operator[](i);
        /*
        low = 0;
        high = EXCLUDE_LIST.size() - 1;
        isFound = false;
        */
        
        for (vector<string>::const_iterator excludeVal = EXCLUDE_LIST.begin(); excludeVal != EXCLUDE_LIST.end(); ++excludeVal) {
            if (curr_CloudVal.first == *excludeVal) {
                m_cloud->RemoveAt(*excludeVal);
                i--;
            }
        }
        // binary search
        /************************/
        /*
        while (low <= high && !isFound) {
            mid = (low + high) / 2;
            // find the mid value in exclude list
            curr_ExcludeVal = EXCLUDE_LIST.at(mid);

            // if the value is in the exclude list
            if (curr_ExcludeVal == curr_CloudVal.first) {
                m_cloud->RemoveAt(curr_ExcludeVal);
                isFound = true;
            }
            else if (curr_CloudVal.first > curr_ExcludeVal) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        */
        /**********************/
    }

}

// Name: RemoveSingles
   // Desc: Asks the user if they would like to remove words with a frequency of 1
   //       Should use the overloaded [] NOTE: Don't forget m_cloud is a pointer!
   // Preconditions: m_cloud is populated
   // Postconditions: m_cloud will have no words with a frequency of 1
void WordCloud::RemoveSingles() {
    LL<string>* curr = m_cloud;
    int numRemoved = 0;
    for (int i = 0; i < curr->GetSize(); i++) {
        string key = curr->operator[](i).first;
        int freq = curr->operator[](i).second;
        if (freq == 1) {
            curr->RemoveAt(key);
            numRemoved++;
            i--;
        }
    }
    cout << numRemoved << " words removed" << endl;
}

// Name: Export
    // Desc: Iterates through m_cloud and exports to file "data:frequency"
    // Preconditions: m_cloud is populated
    // Postconditions: New export file is created with "data:frequency" one on each line
void WordCloud::Export() {
    string filename = "*.txt";
    cout << "What would you like to call the export file?" << endl;
    cin >> filename;

    ofstream newFile(filename);
    for (unsigned int i = 0; i != m_cloud->GetSize(); i++) {
        newFile << m_cloud->operator[](i).first << SEPARATOR
            << m_cloud->operator[](i).second << NEWLINE;
    }
    newFile.close();
    cout << "Output to exportFile: " << filename << endl;
    cout << m_cloud->GetSize() << "unique words exported" << endl;
}

// Name: Start
    // Desc: Calls LoadFile, RemoveCommon, Diplay, and Export 
    // Preconditions: None (filename is available)
    // Postconditions: None
void WordCloud::Start() {
    string usrResponse;
    LoadFile();
    RemoveCommon();
    
    cout << "Would you like to remove all words with a frequency of 1?" << endl;
    cin >> usrResponse;
    RemovePunct(usrResponse);
    if (usrResponse == SIN_YES || usrResponse == FULL_YES) {
        RemoveSingles();
    }
    else {
        cout << "0 words removed" << endl;
    }
    cout << *m_cloud << endl;
    Export();

}

/*
string m_fileName; //Name of the input file
    LL<string>* m_cloud; //LL to store all data
*/
