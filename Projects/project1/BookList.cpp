/*
 * author: Randy Rizo
 * version: 1.0
 * Booklist utilizes the book list class.It will add and print book list from file
 * to console.
 */

#include "BookList.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

// constructor
BookList::BookList(int cap) {
    bookList = new Book[cap];
    capacity = cap;
    numBooks = 0;
}

// unique value for book.
int BookList::ibsnCount = 0;


BookList::~BookList() {
    delete [] bookList;
}


// add books to array
void BookList::add(string author, string title, string year) {
    if (numBooks >= capacity) resize();

    bookList[numBooks].isbn = numBooks + 1;
    bookList[numBooks].author = std::move(author);
    bookList[numBooks].title = std::move(title);
    bookList[numBooks].year = std::move(year);

    // increment number of books.

    numBooks++;
}

int BookList::size() const {
    return numBooks;
}

string BookList::to_string() const {
    string bString;
    // for loop through array
    for (int i = 0; i < numBooks; i++) {
        bString += (::to_string(bookList[i].isbn) + ". " +
                       bookList[i].author + ", " +
                       bookList[i].title + ", " +
                       bookList[i].year +"\n");
    }
    return bString;
}

// update capacity of BookList
void BookList::resize() {
    capacity *= 2;
    // temp array with new max
    Book* tempArr = new Book[capacity];
    // copy contents of original array to new array
    for (int i = 0; i < numBooks; i++)
        tempArr[i] = bookList[i];
    // delete original array
    delete [] bookList;
    // reassign original array
    bookList = tempArr;
}


int BookList::load(const string& file) {
    // single line read from file
    string line;
    // file
    ifstream inFile;
    // open file and read line by line.
    inFile.open(file);
    if(inFile.is_open()) {
        // while there is value in each line.
        while(getline(inFile, line)) {
            // create instance of class book
            Book printbook;
            stringstream lineStream(line);
            for (int i = 0; getline(lineStream, line, ','); i++) {
                if (i==0) printbook.author = line;
                if (i==1) printbook.title = line;
                if (i==2) printbook.year = line;
            }
            add(printbook.author, printbook.title, printbook.year);
        }
        // close file
        inFile.close();
        return 0;
    }
    inFile.close();
    return -1;
}
string BookList::bookInfo(int index) {
    stringstream ss;

    ss << bookList[index - 1].isbn << ", "
       << bookList[index - 1].author << ", "
       << bookList[index - 1].title << ", "
       << bookList[index - 1].year;

    return ss.str();
}