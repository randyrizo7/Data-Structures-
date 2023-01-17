// Author Name: Randy Rizo
// Filename: LInkedlist.h
// Date : 10-22-22
// Purpose: Specification file for lab4.cpp

#ifndef LAB4_LINKEDLIST_H
#define LAB4_LINKEDLIST_H

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class LinkedList {
public:
    LinkedList();
    // Constructor that takes capacity value
    // Pre condition:
    // Post condition: struct linkedlist is created,
    ~LinkedList();
    // Destructor
    // Pre condition: none
    // Post condition: deallocate  from heap

    T getLastNegative();
    // get last negative
    // Precondition: negative
    // Post condition : return true and return last negative

    string to_string() const;
    // Returns string representation of lab4
    // Pre condition: none
    // Post condition: return string

    void append(T);
    // appends elements from array to linked list
    // Pre condition: specify datatype
    // Post condition:values appended

private:
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    T getLastNegative(T &, Node *);
};

// return zero if no negative.

template <class T>
T LinkedList<T>::getLastNegative() {
    T lastNegative = 0;
    return getLastNegative(lastNegative, head);
}
// recursive fxn to obtain last negative.
template <class T>
T LinkedList<T>::getLastNegative(T &lastNegative, Node* node) {
    if (node == nullptr) return lastNegative;
    if (node->data < 0) lastNegative = node->data;
    return getLastNegative(lastNegative, node->next);
}

// ptr head to null
template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

// fxn for deallocation
template <class T>
LinkedList<T>::~LinkedList() {
    Node * curr;
    while (head != nullptr) {
        curr = head;
        head = head->next;
        delete curr;
    }
}
// fxn to append values
template <class T>
void LinkedList<T>::append(T num) {
    Node* newNode = new Node;
    newNode->data = num;
    newNode->next = nullptr;
    Node* curr = head;
    if (head == nullptr) {
        head = newNode;
    } else {
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode ;
    }
}

// fxn to stringify
template <class T>
string LinkedList<T>::to_string() const {
    stringstream ss;
    Node * curr = head;
    while (curr != nullptr) {
        ss << curr->data << " ";
        curr = curr->next;
    }
    ss << "\n";
    return ss.str();
}

#endif //LAB4_LINKEDLIST_H
