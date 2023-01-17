#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    // set constants
    const int CAPACITY = 100;
    const int BOOK_COUNT=55;
    // Declare variables for files and strings.
    ifstream inFile;
    string filename, memberName, memberRatings;
    int memberCount = 0;
    int rating;
    // import stringstream.
    stringstream stream;

    // Get the file name,
    cout << "Enter rating file: ";
    cin >> filename;

    // Declare the needed arrays
    string * members = new string[CAPACITY];
    int ** ratings = new int*[CAPACITY];
    for (int i = 0; i < CAPACITY; i++)
        ratings[i] = new int[CAPACITY];

    // open and save member names and ratings to arrays
    inFile.open(filename);
    if(inFile.is_open()) {
        while(getline(inFile, memberName)) {
            members[memberCount] = memberName;
            getline(inFile, memberRatings);
            stream.str(memberRatings);
            ratings[memberCount] = new int[BOOK_COUNT];
            for (int j = 0; j < BOOK_COUNT; j++) {
                stream >> rating;
                ratings[memberCount][j] = rating;
            }
            memberCount++;
        }
    } else {
        cout << "Failed to open file " << filename << endl;
        return -1;
    }

    // close file.
    inFile.close();



    // Print arrays
    for (int i = 0; i < memberCount; i++) {
        cout << members[i] << endl;
        for (int j = 0; j < BOOK_COUNT; j++)
            cout << ratings[i][j] << " ";
        cout << endl;
    }

    // Deallocate array memory
    delete [] members;
    for (int i = 0; i < CAPACITY; i++)
        delete [] ratings[i];
    delete [] ratings;

    // Set ptr to nullptr
    members = nullptr;
    ratings = nullptr;
}

