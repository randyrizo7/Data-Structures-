// AUTHOR:   Randy RIzo
// FILENAME: p1.cpp
// DATE:     October 17, 2022,
// PURPOSE:  The purpose of this class is to utilize the ratings and books files
//           to create a program that allows users to create an account,
//           give ratings to a book, get recommendations for a book and
//           suggest users with similar tastes in books.
// PROCESS:  Read files and allocate information to 2d dynamic arrays
// OUTPUT:   Various outputs to the terminal based on menu options chosen by
//           the user.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"

using namespace std;

void welcome();
// Prints welcome message
// IN: none
// MODIFY: none
// OUT: message

int landingPage();
// Landing page for the application
// IN: none
// MODIFY: none
// OUT: determined by user input

int userMenu();
// The landing page for logged in user
// IN: none
// MODIFY: none
// OUT: determined by user input

void rateBook(RatingList&, BookList&, int);
// rate specific book from book array.
// IN: argument of RatingList and BookList, and user account
// MODIFY: none
// OUT: none

void viewRatings(BookList&, MemberList&, RatingList&, int);
// Prints the ratings table for books.
// IN: argument of BookList, MemberList, and RatingList, and user account
// MODIFY: none
// OUT: none

void addMember(MemberList&, RatingList&);
// Adds new member to application
// IN: arguments of MemberList and RatingList
// MODIFY: none
// OUT: none

void addBook(BookList&, RatingList&);
// Adds a new book into application
// IN: arguments of BookList and RatingList
// MODIFY: none
// OUT: none

void logInLogic(BookList&, MemberList&, RatingList&);
// Log in logic for user.
// IN: arguments of BookList, MemberList, and RatingList
// MODIFY: none
// OUT: user

void viewRecs(BookList&, MemberList&, RatingList&, int);
// Prints recommended books for member
// IN: arguments of BookList, MemberList, and RatingList, and member account
// MODIFY: none
// OUT: none

void readBookFile(BookList&, const string&);
// Given the arguments of MemberList and RatingList, iterate
// read/ load and assign BooksFile
// IN: arguments of BookList and string
// MODIFY: none
// OUT: none

void readRatingFile(MemberList&, RatingList&, const string&);
// use of arguments of MemberList and RatingList, iterate
// read/ load and assign ratingsFile
// IN: arguments of BookList, RatingList, and string
// MODIFY: none
// OUT: none


void goodBye();
// prints goodbye message after exiting application.
// IN: none
// MODIFY : none
// OUT: none

int main() {

    const int SIZE = 100;           // set size to 100
    int userInput;                     // user's choice
    string bookArr, ratingArr;    // the variables holding files

    BookList bookList(SIZE);        // declare class BookList
    MemberList memberList(SIZE);    // declare class MemberList
    RatingList ratingList(SIZE);    // declare class RatingList

    welcome();

    cout << "Enter books file: ";
    cin >> bookArr;
    readBookFile(bookList, bookArr);

    cout << "Enter rating file: ";
    cin >> ratingArr;
    readRatingFile(memberList, ratingList, ratingArr);

    cout << "\n# of books: " << bookList.size() << endl;
    cout << "# of memberList: " << memberList.size() << endl;

    // do while loop to determine userInput to execute proper function.
    // if user does not type in valid input, keep repeating.

    do{
        userInput = landingPage();

        if (userInput == 1)
            addMember(memberList, ratingList);
        else if (userInput == 2)
            addBook(bookList, ratingList);
        else if (userInput == 3)
            logInLogic(bookList, memberList, ratingList);
        else if (userInput < 1 || userInput > 4)
            cout << "\nError input must be between 1-4...  pleaae try again!\n";
        else
            goodBye();
    }while (userInput != 4);



    return 0;
}

int landingPage(){
    int input;      // user's input

    cout << endl;
    cout << "*************- MENU -*************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Login                       *" << endl;
    cout << "* 4. Quit                        *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "Enter a menu option: ";
    cin >> input;

    cout << endl;

    return input;
}

void welcome()
{
    cout << "Welcome to the Book Recommendation Program! This program allows"
            "\nyou to add a member, book and rating. It will also allow,"
            "\nthe user to view ratings after they login in addition to "
            "\ngiving recommendation for books." << endl << endl;
}

void readBookFile(BookList& bookList, const string& bookFile){

    // to hold values from the file
    string fileName, word, author, title, year;
    // loop counter
    int counter;
    // file variable
    ifstream inFile;

    // open the file
    inFile.open(bookFile);

    // read in the file and classify its contents in terms of author, title, and
    // year
    if (inFile){
        string line, key;
        stringstream ss;
        while (getline(inFile, line)){
            counter = 0;
            ss << line;
            while (getline(ss, key, ',')){
                if (counter == 0)
                    author = key;
                else if (counter == 1)
                    title = key;
                else
                    year = key;
                counter++;
            }
            bookList.add(author, title, year);

            // clear stringstream
            ss.clear();
            ss.str("");
        }
    }
    else
        cout << "Error opening file...\n";

    //close file
    inFile.close();
}

void readRatingFile(MemberList& memberList, RatingList& ratingList,
                    const string& ratingFile) {

    // to hold the values from the file
    string line;
    // loop control variable
    int counter = 0;
    // file variable
    ifstream infile;

    //read file once opened
    infile.open(ratingFile);

    // determine if the file can be opened
    if (infile) {
        // assign contents into either members array or ratings 2D array

        while (getline(infile, line)) {

            // determine which line to allocate too
            if (counter % 2 == 0) {
                memberList.add(line);
            }
            else {
                ratingList.add(line);
            }
            counter++;
        }
    }else
        cout << "Error opening file...\n";

    // close file
    infile.close();
}



void addMember(MemberList& memberList, RatingList& ratingList){
    // initiate name variable of new member
    string name;

    cout << "Enter new member name: ";
    cin.ignore();
    getline(cin, name);

    memberList.add(name);
    ratingList.resizeRow();

    cout << memberList.to_string();
}

void addBook(BookList& bookList, RatingList& ratingList){
    string aAuthor, aTitle, aYear;
    cout << "Enter the author of the new book: ";
    cin.ignore();
    getline(cin, aAuthor);
    cout << "Enter the title of the new book: ";
    getline(cin, aTitle);
    cout << "Enter the year (or range of years) of the new book: ";
    cin >> aYear;

    bookList.add(aAuthor, aTitle, aYear);
    ratingList.resizeCol();

    cout << bookList.to_string();
}

void logInLogic(BookList& bookList, MemberList& memberList, RatingList& ratingList){

    // variables to hold user account info and user input
    int acc;
    int userInput;
    cout << "Please enter member account number: ";
    cin >> acc;
    cout << memberList.name(acc) << ", you are logged in!\n";

    // do while loop; determine function to execute based on user input
    do {
        userInput = userMenu();

        if (userInput == 1)
            addMember(memberList, ratingList);
        else if (userInput == 2)
            addBook(bookList, ratingList);
        else if (userInput == 3)
            rateBook(ratingList,bookList, acc);
        else if (userInput == 4)
            viewRatings(bookList, memberList, ratingList, acc);
        else if (userInput == 5)
            viewRecs(bookList, memberList, ratingList,
                               acc);
        else if (userInput < 1 || userInput > 6)
            cout << "Error! must be between 1 - 6 ... try again!\n";

    }while (userInput != 6);

}

int userMenu(){
    int userInput;     // user input

    cout << endl;
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Rate book                   *" << endl;
    cout << "* 4. View ratings                *" << endl;
    cout << "* 5. See recommendations         *" << endl;
    cout << "* 6. Logout                      *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "Enter a menu option: ";
    cin >> userInput;

    if (userInput != 6)
        cout << endl;

    return userInput;
}

void rateBook(RatingList& ratingList, BookList& bookList, int user){

    // variables to hold user input
    char input = 'y';
    int rating;
    // hold book ISBN
    int ISBN;




    cout << "Enter the ISBN for the book you'd like to rate: ";
    cin >> ISBN;

    // check if user has already rated chosen book
    if (ratingList.returnOneRating(user, ISBN) != 0){
        cout << "You have already rated this book." << bookList.bookInfo(ISBN)
             << "=> rating: " << ratingList.returnOneRating(user, ISBN) << endl;
        cout << "Would you like to give it a new rating? (y/n)? ";
        cin >> input;
    }

    // rate the book
    if (input == 'y' || input == 'Y') {
        cout << "Enter your rating: ";
        cin >> rating;

        ratingList.rate(user, ISBN, rating);

        cout << "Your new rating for " << bookList.bookInfo(ISBN)
             << " => rating: " << ratingList.returnOneRating(user, ISBN) << endl;
    }
}

void viewRatings(BookList& bookList, MemberList& memberList,
                 RatingList& ratingList, int user){
    cout << memberList.name(user) << "'s ratings...\n";

    // iterate over memberList and view rating.
    for (int i = 0; i < bookList.size(); i++){
        cout << bookList.bookInfo(i + 1) << " => rating: "
             << ratingList.returnOneRating(user, i + 1) << endl;
    }
}

void viewRecs(BookList& bookList, MemberList& memberList,
              RatingList& ratingList, int user){

    int sum;
    int tempSum;
    int index;
    int tempIndex;

    // index that has the most max sum
    for (int i = 0; i < memberList.size(); i++){
        tempIndex = i;
        tempSum = 0;
        if (i != user - 1) {
            for (int k = 0; k < bookList.size(); k++) {
                tempSum += ratingList.returnOneRating(user, k + 1) *
                          ratingList.returnOneRating(i + 1, k + 1);
            }
            if (i > 0){
                if (tempSum > sum){
                    sum = tempSum;
                    index= tempIndex;
                }
            }
            else{
                sum = tempSum;
                index = tempIndex;
            }
        }
    }

    cout << "You have similar taste in books as "
         << memberList.name(index + 1) << "!\n\n";

    // print 5 ratings recommended books
    cout << "Here are the books they really liked:\n";
    for (int i = 0; i < bookList.size(); i++){
        if (ratingList.returnOneRating(user, i + 1) == 0 &&
            ratingList.returnOneRating(index + 1, i + 1) == 5){
            cout << bookList.bookInfo(i + 1) << endl;
        }
    }
    cout << "\nAnd here are the books they liked:\n";

    for (int i = 0; i < bookList.size(); i++){
        if (ratingList.returnOneRating(user, i + 1) == 0 &&
            ratingList.returnOneRating(index + 1, i + 1) == 3){
            cout << bookList.bookInfo(i + 1) << endl;
        }
    }
}

void goodBye()
{
    cout << endl << "Until next time! Thank you for using the Book "
                    "Recommendation App!" << endl;
}

// /home/fac/mthayer/submit/22fq5005/files/p1-files/books.txt