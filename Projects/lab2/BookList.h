/*
 * @author: Randy Rizo
 * @version: 1.0
 *
 * Structure of BookList class with declared variables.
 */

#ifndef LAB2_BOOKLIST_H
#define LAB2_BOOKLIST_H

#include <string>
using namespace std;

class BookList {
public:
    // Constructor
    BookList(int);

    // destructor
    ~BookList();

    // add an element to array
    void add(string, string, string);

    // number of elements in array
    int size() const;

    // return string representation
    string to_string() const;

    // load books from file
    int load(string);




private:
    struct Book {
        // book year
        string year;
        // book author
        string author;
        // title of book
        string title;
        // book ibsn
        int isbn;
    };

    // pointer to book array
    Book * bookList;

    //count
    static int ibsnCount;

    // book array capacity
    int capacity;

    // number of books
    int numBooks;

    // when full resize array,
    void resize();

};


#endif //LAB2_BOOKLIST_H