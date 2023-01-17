// AUTHOR:   Randy Rizo
// FILENAME: lab5.cpp
// DATE:     November 5th, 2022
// PURPOSE:  The purpose of this class is to record and display the time it
//           takes for each sorting algorithm.
// INPUT:
// OUTPUT:   Outputs times for each algorithm
//


#include "Sort.h"
#include <vector>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
using namespace std;

//
int counter(int);

vector<int> createVector(int);
void welcome();
// Welcome user to program and provide introduction
// IN: none
// MODIFY: none
// OUT: none
void goodbye();
// Display goodbye message after user is done.
// IN: none
// MODIFY: none
// OUT: none


void runSort(vector<int> &, int);
// run sorting algorithms
// IN: values
// MODIFY: none
// OUT: none


int main() {

    // display welcome message
    welcome();
    // minimum variable
    const int MIN = 40000;
    // maximum varibale
    const int MAX = MIN * pow(2, 9);

    // for loop to generate headers for each sorting algortign
    for (int i = 0; i < 3; i++) {

        cout << "RUN TRIAL " << i + 1 << endl;
        vector<int> randVector;

        for (int i = 0; i <= counter(MAX); i++)
            cout << " ";
        cout << "         MERGE ";
        cout << "      HEAP   ";
        cout << "     QUICK ";
        cout << "      INTRO ";
        cout << "       INSERTION" << endl;
        for (int n = MIN; n <= MAX; n = n * 2) {
            randVector = createVector(n);
            for (int i = 0; i < counter(MAX) - counter(n); i++)
                cout << " ";
            cout << n << " Values | ";
            runSort(randVector, n);
        }
    }
    goodbye();
    return 0;


}

void welcome(){

    //initiate the welcome message
    string welcomeMessage = "\nWelcome to the Runtime of Sorts!!\n "
                            "\nThis program will show the calculation runtime of "
                            "\ndifferent sorting methods and display the times "
                            "\nfor each sorting method.\n\n";

    //print welcome message
    cout << welcomeMessage;
}

void goodbye(){

    //initiate the welcome message
    string goodbyeMessage = "\nThanks for using the Runtime sort app! ";

    //print welcome message
    cout << goodbyeMessage;
}

// fxn initiate counter up until number is reached
int counter(int number) {
    int count = 0;
    while (number != 0) {
        number = number / 10;
        count++;
    }
    return count;
}

void runSort(vector<int> &vec, int n) {
    vector<int> copyVec;
    clock_t t;

    copyVec = vec;
    t = clock();
    mergesort(copyVec.begin(), copyVec.end());
    t = clock() - t;
    cout << fixed << setprecision(6) << ((float) t) / CLOCKS_PER_SEC << "s | ";

    copyVec = vec;
    t = clock();
    heapsort(copyVec.begin(), copyVec.end());
    t = clock() - t;
    cout << ((float) t) / CLOCKS_PER_SEC << "s | ";

    copyVec = vec;
    t = clock();
    quicksort(copyVec.begin(), copyVec.end());
    t = clock() - t;
    cout << ((float) t) / CLOCKS_PER_SEC << "s | ";

    copyVec = vec;
    t = clock();
    sort(copyVec.begin(), copyVec.end());
    t = clock() - t;
    cout << ((float) t) / CLOCKS_PER_SEC << "s | ";

    if (n <= 640000) {
        copyVec = vec;
        t = clock();
        insertionSort(copyVec.begin(), copyVec.end());
        t = clock() - t;
        cout << ((float) t) / CLOCKS_PER_SEC << "s ";
    }
    cout << endl;
}

vector<int> createVector(int n) {
    random_device rnd_device;
    mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist{1, n};

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    vector<int> vec(n);
    generate(begin(vec), end(vec), gen);
    return vec;
}
