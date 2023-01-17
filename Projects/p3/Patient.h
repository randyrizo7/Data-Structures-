// AUTHOR:   Randy Rizo
// FILENAME: patient.h
// DATE:     November 20th, 2022
// PURPOSE:  Implementation of Patient.h
// INPUT:
// OUTPUT:
//


#ifndef P3_PATIENT_H
#define P3_PATIENT_H
#include <string>
#include <sstream>
using namespace std;

class Patient {
public:
    Patient(string, int, int);
    ~Patient();
    // Copy Constructor
    Patient(const Patient &);
    // overloadrr comparison operatrs
    bool operator<(const Patient &);
    // determine patient priority
    bool operator>(const Patient &);
    // constructor equal to overload operator
    const Patient &operator=(const Patient &);

    // get patient name
    string getName();
    // stringify energency room priority queue.
    string to_string();
    // get patient arrival order
    int getArrivalOrder();
    // get patient priority code.
    int getPriorityCode();

private:
    // Patient name
    string name;
    // patient arrival number
    int arrivalOrder;
    // Priority code of patient
    int priorityCode;
};

Patient::Patient(string name, int priorityCode, int arrivalOrder) {
    this->name = name;
    this->priorityCode = priorityCode;
    this->arrivalOrder = arrivalOrder;
}

Patient::~Patient() { }

Patient::Patient(const Patient &obj) {
    this->name = obj.name;
    this->priorityCode = obj.priorityCode;
    this->arrivalOrder = obj.arrivalOrder;
}

const Patient &Patient::operator=(const Patient &obj) {
    this->name = obj.name;
    this->priorityCode = obj.priorityCode;
    this->arrivalOrder = obj.arrivalOrder;
    return *this;
}

bool Patient::operator<(const Patient &obj) {
    return this->priorityCode < obj.priorityCode ||
           (this->priorityCode == obj.priorityCode
            && this->arrivalOrder < obj.arrivalOrder);
}

bool Patient::operator>(const Patient &obj) {
    return !(*this < obj);
}

string Patient::getName() {
    return this->name;
}



int Patient::getArrivalOrder() {
    return arrivalOrder;
}

int Patient::getPriorityCode() {
    return priorityCode;
}

string Patient::to_string() {
    return getName();
}



#endif //P3_PATIENT_H
