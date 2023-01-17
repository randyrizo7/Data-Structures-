//
// Created by Randy Rizo on 11/30/22.
//

// Author : Randy Rizo
// File: wordcounter.h
// Date: 11/29/2022
//
#ifndef P4_WORDCOUNTER_H
#define P4_WORDCOUNTER_H
#include <sstream>
#include <functional>
#include <iostream>
using namespace std;

class WordCounter {
public:
    explicit WordCounter(int);
    // Constructor
    // Precondition: capacity
    // Postcondition: initialize uniqueWordCount and totalWordCount to 0,
    //                capacity to input integer, and each bucket to nullptr

    ~WordCounter();
    // Destructor
    // Precondition: none
    // Postcondition: call destroyLinkedList function to delete LinkedList

    WordCounter(const WordCounter &);
    // Copy constructor
    // Precondition: receive a reference of WordCounter
    // Postcondition: assign data from old WordCounter to the new

    WordCounter & operator = (const WordCounter *&);
    // Overload constructor
    // Precondition: receive a reference of WordCounter
    // Postcondition: assign data from old WordCounter to the new and return its
    //                reference

    int addWord(string);
    //  Add word to hashTable
    // Precondition: string word
    // Postcondition: return the word's frequencies

    double getWordCount(string &);
    // Return frequencies of specified word
    // Precondition: a reference of string
    // Postcondition: return frequencies of specified word

    double getTotalWordCount() const;
    // Return total word count
    // Precondition: none
    // Postcondition: return total word count

    void removeWord(string &);
    // Remove the words from the hashtable
    // Precondition: a reference of string
    // Postcondition: remove the words from the hashtable

    double getCapacity() const;
    // Return capacity
    // Precondition: none
    // Postcondition: return capacity

    double getUniqueWordCount() const;
    // Return unique word count
    // Precondition: none
    // Postcondition: return unique word count

    bool empty();
    // Return true is hashTable is empty
    // Precondition: none
    // Postcondition: Return true is hashTable is empty

private:
    // create struct
    struct Node{
        // string varibnale to hold word
        string word;
        // int value of frequency
        int freq{};
        // ptr to next node
        Node * next{};      // pointer to next Node
    };

    // declaration of node array
    Node ** NodeArray;
    // hashtable capacity
    int capacity;
    // unique word counter
    int uniqueWordCount;
    // cpunter for total word count
    int totalWordCount;

    void destroyNodeArray();
    //  Destroy the linked list
    // Precondition: none
    // Postcondition: Destroy the linked list

    Node ** copyConstructor(Node **) const;
    // Copy old 2D Node to the new one and return the new
    // Precondition: 2D Node
    // Postcondition: return the new 2D Node

    Node * copyConstructorHelper(Node *) const;
    // Copy data from old Node to the new one and return the new
    // Precondition: Node
    // Postcondition: return the new Node

    int addNewNode(Node *& ,string &);
    // Add new node in the end of the linked list and return its frequencies
    // Precondition:
    // Postcondition:

    void removeWord(Node *&, Node *&, string &);
    // Remove removed words from the linked list
    // Precondition: three references of two Nodes and a string
    // Postcondition: remove removed words from the linked list

    double getWordCount(Node *&, string &);
    // Return frequencies of the specified word
    // Precondition: references of a Node and a string
    // Postcondition: return frequencies of the specified word

};

WordCounter::WordCounter(int cap) {

    // capacity varibale for hashtable
    capacity = cap;
    // node array
    NodeArray = new Node * [cap];
    // unique word counter
    uniqueWordCount = 0;
    // total word counter
    totalWordCount = 0;


    // set each bucket to nullptr
    for (int i = 0; i < cap; i++) {
        NodeArray[i] = nullptr;
    }
}

WordCounter::~WordCounter() {
    destroyNodeArray();
}

double WordCounter::getCapacity() const {
    return capacity;
}

double WordCounter::getUniqueWordCount() const {
    return uniqueWordCount;
}

double WordCounter::getTotalWordCount() const {
    return totalWordCount;
}


void WordCounter::destroyNodeArray() {
    // declare a node
    Node * cur;

    // delete each linked List
    for(int i = 0; i < capacity; i++) {
        cur = NodeArray[i];
        while (cur != nullptr) {
            Node * tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }

    // delete NodeArray
    delete [] NodeArray;
}

WordCounter::WordCounter(const WordCounter & obj) {
    capacity = obj.capacity;
    uniqueWordCount = obj.uniqueWordCount;
    totalWordCount = obj.totalWordCount;

    // call the function to assign old NodeArray to the new
    NodeArray = copyConstructor(obj.NodeArray);

}

WordCounter::Node ** WordCounter::copyConstructor(Node ** arrayList) const {
    Node ** newNodeArray = new Node * [capacity];       // declare a new 2D Node

    // assign each bucket from old NodeArray to the new
    for (int i = 0; i < capacity; i++)
        newNodeArray[i] = copyConstructorHelper(arrayList[i]);

    return newNodeArray;
}

WordCounter::Node * WordCounter::copyConstructorHelper(Node * curr) const {
    Node * newNode = new Node();        // declare a new Node

    // assign old data from old Node to the new
    if(curr == nullptr) {
        return curr;
    }
    else {
        newNode->word = curr->word;
        newNode->freq = curr->freq;

        // call recursive copyConstructorHelper function
        newNode->next = copyConstructorHelper(curr->next);
    }

    return newNode;
}

WordCounter & WordCounter::operator = (const WordCounter *& obj) {
    if (this != obj){

        // destroy old NodeArray
        destroyNodeArray();
        capacity = obj->capacity;
        uniqueWordCount = obj->uniqueWordCount;
        totalWordCount = obj->totalWordCount;

        // Assign data from old NodeArray Node to the new
        NodeArray = copyConstructor(obj->NodeArray);
    }

    return *this;
}

bool WordCounter::empty() {
    // check if the NodeArray is empty
    for (int i = 0; i < capacity; i++)
        if (NodeArray[i] != nullptr)
            return false;

    return true;
}

int WordCounter::addWord(string addedWord) {
    // find the index of the NodeArray
    size_t hashCode = hash<string>{}(addedWord);
    int index = hashCode % capacity;

    Node * ptr = NodeArray[index];
    Node * prev = nullptr;

    // check if the first bucket of index is empty to add a new Node
    if(ptr == nullptr) {
        uniqueWordCount++;
        totalWordCount++;
        Node * newNode = new Node;

        newNode->word = addedWord;
        newNode->freq = 1;
        newNode->next = nullptr;

        NodeArray[index] = newNode;
        return NodeArray[index]->freq;
    }

    // traverse to find the added word
    while (ptr != nullptr){
        if (addedWord == ptr->word){
            ptr->freq++;
            totalWordCount++;

            return ptr->freq;
        }
        else {
            prev = ptr;
            ptr = ptr->next;
        }
    }

    // add a wew Node to the end of the linked list
    return addNewNode(prev, addedWord);
}

int WordCounter::addNewNode(Node *& prev, string & addedWord) {
    uniqueWordCount++;
    totalWordCount++;
    Node * newNode = new Node;      // declare a new Node

    newNode->word = addedWord;
    newNode->freq = 1;
    newNode->next = nullptr;

    prev->next = newNode;

    return newNode->freq;
}

void WordCounter::removeWord(string & removedWord) {
    Node * ptr;             // declare a Node
    Node * prevOrTmp;       // declare a Node

    // find the index of the NodeArray
    size_t hashCode = hash<string>{}(removedWord);
    int index = hashCode % capacity;

    ptr = NodeArray[index];

    // check if the first bucket of index is empty
    if (ptr == nullptr)
        return;

        // check if the first bucket of index is empty to add a new Node
    else if (ptr->word == removedWord){
        uniqueWordCount--;
        totalWordCount -= ptr->freq;
        prevOrTmp = ptr->next;
        delete ptr;
        NodeArray[index] = prevOrTmp;
    }

        // traverse to find the removed word
    else {
        prevOrTmp = ptr;
        ptr = ptr->next;

        // call recursive removedWord function to find the word
        removeWord(prevOrTmp, ptr, removedWord);
    }
}

void WordCounter::removeWord(Node *& prev, Node *& ptr, string & removedWord) {
    // traverse to find the removed word
    if (ptr != nullptr){
        if (ptr->word == removedWord){
            uniqueWordCount--;
            totalWordCount -= ptr->freq;
            prev->next = ptr->next;
            delete ptr;
            return;
        }
        else {
            prev = ptr;
            ptr = ptr->next;
            removeWord(prev, ptr, removedWord);
        }
    }
}



double WordCounter::getWordCount(string & specifiedWord) {
    // find the index of the NodeArray
    size_t hashCode = hash<string>{}(specifiedWord);
    int index = hashCode % capacity;

    Node * ptr = NodeArray[index];

    // call the recursive specifiedWord function to find the word and return its
    // frequencies
    return getWordCount(ptr, specifiedWord);
}

double WordCounter::getWordCount(Node *& ptr, string & specifiedWord) {
    // traverse to find the specified word
    if (ptr == nullptr)
        return 0;
    else{
        if (ptr->word == specifiedWord)
            return ptr->freq;
        else
            return getWordCount(ptr->next, specifiedWord);
    }
}



#endif //P4_WORDCOUNTER_H
