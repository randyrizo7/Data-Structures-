// Randy Rizo
//  File p2.cpp
// Date: 10/30/2022
// Purpose: The program tests insert, contains, remove, empty, size,
//          getLeafCount, getHeight, getLevel, getInOrderTraversal,
//          getPreOrderTraversal, getPostOrderTraversal, and getAncestors of
//          BST.h


#include <iostream>
#include <fstream>
#include "BST.h"

using namespace std;

void welcome();
// Print welcome message out
// IN: none
// MODIFY: none
// OUT: welcome message
void goodBye();
// Print goodBye message out
// IN: none
// MODIFY: none
// OUT: goodBye message
template <typename T>
void displayTreeStats(BST<T> &);
// Print BST statistics
// IN: BST
// MODIFY: none
// OUT: BST stats
template <typename T>
void displayOrderTraversal(BST<T> &);
// Print BST traversal order
// IN: BST
// MODIFY: none
// OUT: BST traveralvalues in order

template <typename T>
void displayLevelAndAncestors(BST<T> &, T);
// Print BST ancestors and levels
// IN: BST
// MODIFY: none
// OUT: BST levels and ancestors of binary search tree


int main() {

    int input;
    string sInput;
    // ss to file name path from user
    ifstream inputFile;
    // string variable to hold file name
    string fileName, str;
    //
    int testIntArray[] = {20, 40, 10, 70, 99, -2, 59, 43};
    string testStringArray[] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron", "opal"};


    // print welcome message
    welcome();

    cout << "------------------------------" << endl;
    cout << "- INTEGER BINARY SEARCH TREE -" << endl;
    cout << "------------------------------" << endl ;

    cout << "-- CREATE BST --" << endl;
    BST<int> intBST;
    displayTreeStats(intBST);
    // get filename/ path from user
    fileName = "integers.dat";
    inputFile.open(fileName);
    if(!inputFile.is_open()) {
        cout << "\nEnter integer file: ";
        getline(cin, fileName);
        inputFile.open(fileName);
        if(!inputFile.is_open()) {
            cerr << "Could not open the file - " << fileName << endl;
            return EXIT_FAILURE;
        }
    }
    cout << endl;

    cout << "-- TEST INSERT --" << endl;

    cout << "Inserting in this order: ";
    while (inputFile >> input) {
        cout << input << " ";
        intBST.insert(input);
    }
    cout << endl;
    displayTreeStats(intBST);
    cout << endl;

    cout << "-- TEST TRAVERSALS --" << endl;
    displayOrderTraversal(intBST);
    cout << endl;

    cout << "-- TEST LEVEL & ANCESTORS --" << endl;
    str = intBST.getPreOrderTraversal();
    stringstream ss(str);

    while(ss >> input)
        displayLevelAndAncestors(intBST, input);

    cout << endl;

    cout << "-- TEST CONTAINS --" << endl;
    for (int val : testIntArray) {
        cout << "contains(" << val <<"): "
             << (intBST.contains(val)?"true":"false") << endl;
    }
    cout << endl;

    cout << "-- TEST REMOVE --" << endl;
    cout << "Removing in this order: ";
    for (int val : testIntArray) {
        cout << val << " ";
        intBST.remove(val);
    }
    cout << endl;
    displayTreeStats(intBST);
    displayOrderTraversal(intBST);
    cout << endl;

    cout << "-- TEST INSERT (again) --" << endl;
    cout << "Inserting in this order: ";
    for (int val : testIntArray) {
        cout << val << " ";
        intBST.insert(val);
    }
    cout << endl;
    displayOrderTraversal(intBST);
    // close file
    inputFile.close();


    cout << "\n==================================================" << endl;

    cout << "-- CREATE BST --" << endl;
    BST<string> stringBST;
    displayTreeStats(stringBST);

    // get filename from user.
    fileName = "strings.dat";
    inputFile.open(fileName);
    if(!inputFile.is_open()) {
        cout << "\nEnter strings file: ";
        getline(cin, fileName);
        inputFile.open(fileName);
        if(!inputFile.is_open()) {
            cerr << "Could not open the file - " << fileName << endl;
            return EXIT_FAILURE;
        }
    }
    cout << endl;

    cout << "-- TEST INSERT --" << endl;

    cout << "Inserting in this order: ";
    while (inputFile >> sInput) {
        cout << sInput << " ";
        stringBST.insert(sInput);
    }
    cout << endl;
    displayTreeStats(stringBST);
    cout << endl;

    cout << "-- TEST TRAVERSALS --" << endl;
    displayOrderTraversal(stringBST);
    cout << endl;

    cout << "-- TEST LEVEL & ANCESTORS --" << endl;
    str = stringBST.getPreOrderTraversal();
    ss.clear();
    ss.str(str);
    while(ss >> str) {
        displayLevelAndAncestors(stringBST, str);
    }
    cout << endl;

    cout << "-- TEST CONTAINS --" << endl;
    for (string val : testStringArray) {
        cout << "contains(" << val <<"): "
             << (stringBST.contains(val)?"true":"false") << endl;
    }
    cout << endl;

    cout << "-- TEST REMOVE --" << endl;
    cout << "Removing in this order: ";
    for (string val : testStringArray) {
        cout << val << " ";
        stringBST.remove(val);
    }
    cout << endl;

    displayTreeStats(stringBST);
    displayOrderTraversal(stringBST);
    cout << endl;

    cout << "-- TEST INSERT (again) --" << endl;
    cout << "Inserting in this order: ";
    for (string val : testStringArray) {
        cout << val << " ";
        stringBST.insert(val);
    }
    cout << endl;
    displayTreeStats(stringBST);
    displayOrderTraversal(stringBST);



    goodBye();

    inputFile.close();
    return 0;
}

void welcome(){
    cout << "Welcome to the BST program!\nThis program tests, insert, "
            "contain, remove, empty, size, getLeafCount,\ngetHeight, "
            "getLevel, getInOrderTraversal, getPreOrderTraversal,\n"
            "getPostOrderTraversal and getAncestors of BST program"
            "functions.\n" << endl;
}

void goodBye(){
    cout << "\n\nThank you for using BST program. GoodBye";
}


template <typename T>
void displayTreeStats(BST<T> &obj) {
    cout <<
         "# of nodes:  " << obj.size() << endl <<
         "# of leaves: " << obj.getLeafCount() << endl <<
         "BST height:  " << obj.getHeight() << endl <<
         "BST empty? " << (obj.empty() ? "true" : "false") << endl;
}

template <typename T>
void displayOrderTraversal(BST<T> &obj) {
    cout <<
         "pre-order:  " << obj.getPreOrderTraversal() << endl <<
         "in-order:   " << obj.getInOrderTraversal() << endl <<
         "post-order: " << obj.getPostOrderTraversal() << endl;
}

template <typename T>
void displayLevelAndAncestors(BST<T> &obj, T val) {
    cout <<
         "level(" << val << "): " << obj.getLevel(val) << ", "
                                                          "ancestors(" << val << "): " << obj.getAncestors(val) << endl;
}