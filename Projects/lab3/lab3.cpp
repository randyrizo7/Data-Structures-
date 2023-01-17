// AUTHOR:   Randy Rizo
// FILENAME: lab3.cpp
// DATE:     10/20/2022
// PURPOSE:  This program prompts user to put in filepath. The program will load/
//           read the file data line by line and determine if each line is
//           a palindrome.
// INPUT:    User input of filepath
// PROCESS:  Program determines if text is palindrome for each line.
// OUTPUT:   Prints each line with result of palindrome or not.

#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
using namespace std;


// prints welcome message when user  runs program .
void welcome(){

    // string to hold welcome message
    string welcomeMessage = "\nWelcome to the palindrome testing "
                            "\ntesting program!\n\n";

    cout << welcomeMessage;
}
// prints goodbye message when user ends program.
void goodbye(){

    // string to hold goodbye message
    string goodbyeMsg = "\nThanks for using Palindrome tester!!";

    cout << goodbyeMsg;
}

// helper fxn to process string from file.
string preProcess(string str) {
    char c;
    int n = str.length();

    // utilize stringstream
    stringstream ss;

    // for loop to iterate over string.
    for (int i = 0; i < n; i++) {
        c = str[i];
        if (!isspace(c)) {
            c = tolower(c);
            ss << c;
        }
    }
    // return string
    return ss.str();
}

// determines if string is palindrome if string is preprocessed.
bool isPalindrome(string str, bool load) {
    if (!load) {
        str = preProcess(str);
        load = true;
    }
    if (str.length() == 0) return true;
    if (str[0] != str[str.length() - 1]) return false;
    return isPalindrome(str.substr(1, str.length() - 2), load);
}

// return palindrome string.
bool stringPalindrome(string data) {
    // input data is processed once
    string str = preProcess(data);
    return isPalindrome(str, true);
}


int main() {

    // declare variables
    bool solution;
    ifstream inputFile;
    string line;

    // call welcome fxn
    welcome();
    // sk user for input
    cout << "Enter the filename: ";
    getline(cin, line);
    cout << endl;
    // open file
    inputFile.open(line);

    // read each line of file.
    if(inputFile.is_open()) {
        while(getline(inputFile, line)) {
            solution = stringPalindrome(line);
            cout << line << (solution?" is":" is NOT")
                 << " a palindrome." << endl;
        }
    } else {
        cout << "File not found!" << endl;
    }

    // close file.
    inputFile.close();

    // call goodbye fxn.
    goodbye();

    return 0;
}


