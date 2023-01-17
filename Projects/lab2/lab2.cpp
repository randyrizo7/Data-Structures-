/*
 * @author:  Randy Rizo
 * @version: 1.0
 * Main will ask user for file path. It will read and print the file contents
 * to the console. This application will print the number of books
 * as well the title and year.
 */

#include <iostream>
#include "BookList.h"
using namespace std;



int main() {
    // create booklist with size 55.
    BookList books(55);
    // hold file name
    string filename;

    // input file name from user
    cout << "Enter your book file: ";
    getline(cin, filename);

    // Load books from file
    if(books.load(filename)) {
        cout << "Failed to load file" << endl;
        return -1;
    };

    // Print books from file
    cout << "# of books: " + to_string(books.size()) << endl;
    cout << books.to_string() << endl;

    return 0;


}