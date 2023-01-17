// Author : Randy Rizo
// File: p4.cpp
// Date: 11/29/2022
// purpose: uses a Hash Table to efficiently solve the following problem: Given a natural language text, generate a
// table of distinct words with the number of occurrences of each word in the text.


#include "WordCounter.h"
#include "CommonWordList.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

string cleanWord(string);
// takes in word and cleans it up-- removes special characters


void testLoop(int &);
// Execute testing sequence

void displayStatistics(WordCounter &);
// display stats

void promptForRemovedWords(string &);
// words to be removed

void analysisStats(WordCounter &, string&);
// display removed words

void removeCommonWords(WordCounter &);
// Remove common words from


void testFile(string &, int &, int &);
// Display the test message and prompt for file name and a capacity

void readInFile(WordCounter &, const string&);
// Read in contents from a file


const char APOSTROPHE_CHAR = '\''; 	// apostrophe character used in cleanWord
const char HYPHEN_CHAR = '-'; 		// hyphen/dash character used in cleanWord

int main() {
    int testTime = 0;

    // populate common words
    CommonWordList::populateWords();

    // test 1
    testLoop(testTime);

    // test 2
    testLoop(testTime);

    return 0;
}

string cleanWord(string s) {
    string result = "";                  // Keep track of the cleaned result.
    unsigned i = 0, length = s.length(); // Input for the for loop.
    for (; i < length; i++) {
        if (isalnum(s[i]))
            result += tolower(s[i]);
        else if (s[i] == APOSTROPHE_CHAR) {
            if (i > 0 && isalnum(s[i-1]))
                result += s[i];
        } else if (s[i] == HYPHEN_CHAR) {
            if (i > 0 && i < (length-1) && isalnum(s[i-1]) &&
                isalnum(s[i+1]))
                result += s[i];
                // If a word ends in a hyphen, we assume it is residue that
                // needs to be paired with the next word. Return the word with
                // the hyphen as a signal to the caller to retain it as residue.
            else if (i > 0 && i == (length-1) && isalnum(s[i-1]))
                result += s[i];
        }
    }
    return result;
}

void removeCommonWords(WordCounter &wc) {
    for (string &s : CommonWordList::getWords())
        wc.removeWord(s);
}

void displayStatistics(WordCounter & hashTable){
    double loadF = hashTable.getUniqueWordCount() / hashTable.getCapacity();

    cout << "\nWord Counter statistics:\n"
            "  #Unique   #Total   Load Factor \n"
            "+---------+--------+-----------+\n";

    // display unique, total, and load factor numbers
    cout << setw(7) << (int)hashTable.getUniqueWordCount();
    cout << setw(10) << (int)hashTable.getTotalWordCount();
    cout << setw(12) << fixed << setprecision(3) << loadF << endl;
}



void testFile(string & fileName, int & capacity, int & testTime){
    testTime++;

    cout << "\n*********************\n"
            "*   Test file # " << testTime << ":  *\n"
                                              "*********************\n\n";

    // prompt for a file name
    cout << "What is the filename: ";
    cin >> fileName;

    // prompt for the capacity of hash table
    cout << "What is the capacity: ";
    cin >> capacity;
}

void testLoop(int & testTime){
    // hash table capacity
    int capacity;
    // strring variables to hold file name and removed words
    string fileName;
    string removed;


    testFile(fileName, capacity, testTime);

    WordCounter hashTable(capacity);

    readInFile(hashTable, fileName);

    removeCommonWords(hashTable);

    WordCounter hashTable2(hashTable);

    displayStatistics(hashTable);

    promptForRemovedWords(removed);

    analysisStats(hashTable2, removed);

    WordCounter hashTable3 = hashTable2;

    displayStatistics(hashTable3);
}



void promptForRemovedWords(string & RemovedWord){
    cout << "\nEnter words (separated by space): ";
    cin.ignore();

    getline(cin,RemovedWord);
}

void analysisStats(WordCounter & hashTable, string & RemovedWord){
    stringstream ss(RemovedWord);
    string token;

    cout << "\nAnalysis of words:\n"
            "  Given Word   Count \n"
            "+------------+-------+\n";

    // display the removed words and the frequency
    while(getline(ss,token,' ')){
        cout << setw(10) << token << setw(8) <<
             setprecision(0) << hashTable.getWordCount(token) << endl;

        hashTable.removeWord(token);
    }

    cout << "\nRemove the following words: " << RemovedWord << endl;
}

void readInFile(WordCounter & hashTable, const string& fileName){
    string allString, strLine, newStr;
    stringstream ss;
    ifstream inFile;

    // open file
    inFile.open(fileName.c_str());
    if (!inFile.is_open()) {
        cout << "ERROR loading file!\n";
    }

    // while loop- read in lines from file
    while(getline(inFile,strLine)) {
        if (strLine[strLine.length() - 1] != '-')
            strLine += " ";

        ss << strLine;
    }

    // while loop to add words to hashtable
    while(getline(ss,newStr, ' ')) {
        if (!newStr.empty() && newStr != "-") {
            hashTable.addWord(cleanWord(newStr));
        }
    }

    // close file
    inFile.close();
}

