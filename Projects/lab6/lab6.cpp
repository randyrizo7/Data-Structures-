// AUTHOR:   Randy Rizo
// FILENAME: lab6.cpp
// DATE:     November 19th, 2022
// PURPOSE:  The purpose of this class is to record and display a hashtable
// OUTPUT:   Outputs has
//

#include "HashTable.h"
#include <iostream>
using namespace std;

void welcome();
void getTest(int*, int, HashTable &);
void putTest(int*, int, HashTable &);
void containsTest(int*, int, HashTable &);
void goodbye();



int main() {
    // declare max capacity
    const int CAPACITY = 4093;
    // test array variable
    int testArray[] = {50184, 77, 0, -1};
    // array variable declaration
    int array[] = {1179, 9702, 7183, 50184, 4235, 644, 77, 3077, 23477, 90777};


    // display welcome message
    welcome();

    // Create new table
    HashTable table(CAPACITY);
    for (int i = 0; i < 4083; i++) {
        // insert random key int
        table.put(i, rand());
    }

    // test put method
    putTest(array, 10, table);
    // test contains method
    containsTest(testArray, 4, table);
    //test get method
    getTest(testArray, 4, table);

    goodbye();


    return 0;
}

void welcome(){

    //initiate the welcome message
    string welcomeMessage = "\nWelcome to the HashTable testing program.\n"
                            "\n"
                            "Creating a new HashTable with capacity 4093 and inserting \n"
                            "4083 random key-value pairs with unique keys.. "
                            "done.\n\n";
    //print welcome message
    cout << welcomeMessage;
}

void goodbye(){

    //initiate the welcome message
    string goodbyeMessage = "\n\nThanks for using the HashTable testing program. \nGoodbye.";

    //print welcome message
    cout << goodbyeMessage;
}


void getTest(int* testArr, int size, HashTable &table) {
    cout << "\nTest Get..." << endl;
    for (int i = 0; i < size; i++) {
        cout << "get("<< testArr[i] << "): " << table.get(testArr[i]) << endl;
    }
}

void putTest(int* testArr, int size, HashTable &table) {
    int value = 120;
    cout << "Inserting 10 additional values\n";
    for (int i = 0; i < size; i++) {
        cout << "(" << testArr[i] << ", " << value << ")"
             << (table.contains(testArr[i]) )
             <<  table.put(testArr[i] , value)<< endl;
        value++;
    }
}

void containsTest(int* testArr, int size, HashTable &table) {
    cout << "\nTest Contains... " << endl;
    for (int i = 0; i < size; i++) {
        cout << "contains("<< testArr[i] << "): "
             << (table.contains(testArr[i]) ? "true" : "false") << endl;
    }
}