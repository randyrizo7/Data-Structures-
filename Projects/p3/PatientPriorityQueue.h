// AUTHOR:   Randy Rizo
// FILENAME: patient.h
// DATE:     November 20th, 2022
// PURPOSE:  Implementation of PatienPriorityQueue.h
// INPUT:
// OUTPUT:
//

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H

#include "Patient.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;



class PatientPriorityQueue {
public:
    PatientPriorityQueue();
    ~PatientPriorityQueue();
    // Copy Constructor
    PatientPriorityQueue(PatientPriorityQueue &);
    //set constructor equal to overload operator
    const PatientPriorityQueue &operator=(PatientPriorityQueue &);

    // Returns the string representation of priority queue
    string to_string();
    // return total num patients still in queue
    int size();
    // Removes the highest priority patient from the queue
    string remove();
    // return highest priority queue
    string peek();
    // add to patient to queue
    void add(string, int);



private:
    // Store the patients in heap order
    vector<Patient> patients;
    // Keep track of the last patient inserted into the heap, so that as patients arrive, they will get assigned proper arrivalOrder (start numbering at 1).
    int nextPatientNumber;
    void moveLeft(int);
    void moveRight(int);
    void swap(int, int);
    void add(string, int, int);
    string remove(int);
    string getPriorityStatus(int);
};


// CONSTRUCTOR

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 0;
}

PatientPriorityQueue::~PatientPriorityQueue() {
    patients.clear();
    nextPatientNumber = 0;
}

PatientPriorityQueue::PatientPriorityQueue(PatientPriorityQueue &obj) {
    this->patients = obj.patients;
    this->nextPatientNumber = obj.nextPatientNumber;
}

const PatientPriorityQueue
&PatientPriorityQueue::operator=(PatientPriorityQueue &obj) {
    this->patients = obj.patients;
    this->nextPatientNumber = obj.nextPatientNumber;
    return *this;
}

// PUBLIC METHODS

int PatientPriorityQueue::size() {
    return patients.size();
}

string PatientPriorityQueue::peek() {
    if (size() == 0) return "";
    return patients.front().to_string();
}

void PatientPriorityQueue::add(string name, int priorityCode) {
    add(name, priorityCode, ++nextPatientNumber);
}


string PatientPriorityQueue::remove() {
    return remove(0);
}

// PRIVATE METHODS

string PatientPriorityQueue::remove(int index) {
    // return empty string when size = 0
    if (size() == 0) return "";
    Patient patient = patients.at(index);
    //  swap current ptient with priority patient,
    if (size() > 1) {
        swap(index, size() - 1);
    }
    // pop (remove) patient
    patients.pop_back();
    // shift list down.
    moveRight(index);

    return patient.to_string();
}


void PatientPriorityQueue::add(string name, int priorityCode, int arrivalOrder)
{
    // create new patient for priority queue;
    Patient patient(name, priorityCode, arrivalOrder);
    // insert Patient in order
    patients.push_back(patient);
    // move patient to appropriate index
    moveLeft(size() - 1);
}


void PatientPriorityQueue::moveLeft(int index) {
    // if index is less than zero or is zero return empty
    if (index <= 0) return;
    int parentIndex = (index - 1) / 2;
    if (patients.at(index) < patients.at(parentIndex)) {
        swap(index, parentIndex);
        moveLeft(parentIndex);
    }
}

void PatientPriorityQueue::moveRight(int index) {
    // create variables for children
    int leftChildIdx = 2 * index + 1;
    int rightChildIdx = 2 * index + 2;
    int swapIndex;

    if (rightChildIdx < size())
        swapIndex = patients.at(leftChildIdx) < patients.at(rightChildIdx)
                    ? leftChildIdx : rightChildIdx;
    else if (leftChildIdx < size())
        swapIndex = leftChildIdx;
    else return;

    // swap patients based on priority
    if (patients.at(index) > patients.at(swapIndex)) {
        swap(index, swapIndex);
        moveRight(swapIndex);
    }
}
string PatientPriorityQueue::to_string() {
    stringstream ss;
    string priorityStatus;
    for (vector<Patient>::iterator patientIt = patients.begin() ;
         patientIt != patients.end(); ++patientIt) {
        priorityStatus = getPriorityStatus(patientIt->getPriorityCode());
        ss
                << setw(7) << right << patientIt->getArrivalOrder()
                << setw(7) << left << " "
                << setw(16) << left << priorityStatus
                << patientIt->to_string()
                << endl;
    }
    return ss.str();
}

// swap fxn swaps patients between two indexes.
void PatientPriorityQueue::swap(int index1, int index2) {
    Patient temp(patients.at(index1));
    patients.at(index1) = patients.at(index2);
    patients.at(index2) = temp;
}



string PatientPriorityQueue::getPriorityStatus(int priorityCode) {
    switch(priorityCode) {
        case 1: return "immediate";
        case 2: return "emergency";
        case 3: return "urgent";
        case 4: return "minimal";
        default: return "";
    }
}
#endif //P3_PATIENTPRIORITYQUEUE_H
