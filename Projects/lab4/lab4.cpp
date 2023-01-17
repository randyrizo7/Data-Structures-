//
// Author: Randy Rizo
// Filename: lab4.cpp
// Date: 10-24-22
// Purpose: The purpose of this lab is to utilize the linkedlist header file.
//          The header file utilizes a template that can read in arrays of multiple
//          datatypes abd return the last negative.
// Input: array
// Process:
// Output:  the last negative and array values


#include <iostream>
#include "LinkedList.h"
using namespace std;

int main() {
    // delclare linked lists and their datatypes.
    LinkedList<double> doubleLinkedList;
    LinkedList<int> intLinkedList;

    // arrays to be read.
    int intarray[] = {3, -2, 5, 12, -2, -4, 5};
    double doublearray[] = {-3.2, 2.14, -5.7, -12.01, -2.99, 4.6, 5.2};

    // populate/ append int array into linked list
    for (int num : intarray) {
        intLinkedList.append(num);
    }
    cout << "Last Negative Number: " << intLinkedList.getLastNegative()  << endl;
    cout << "Linked List Values: " << intLinkedList.to_string() << endl;

    // populate/ append double array into linked list
    for (double num : doublearray) {
        doubleLinkedList.append(num);
    }
    cout << "Last Negative Number: " << doubleLinkedList.getLastNegative()  << endl;
    cout << "Linked List Values: " << doubleLinkedList.to_string() << endl;
}