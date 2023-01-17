#include "MemberList.h"
#include <iostream>
#include <sstream>
#include <utility>
using namespace std;

MemberList::MemberList(int cap) {
    memberList = new Member[cap];
    capacity = cap;
    numElements = 0;
    aAccount = 1;
}

MemberList::~MemberList() {
    delete [] memberList;
}

void MemberList::add(string aName) {
    if (numElements >= capacity)
        resize();

    memberList[numElements].name = std::move(aName);
    memberList[numElements].account = aAccount;

    aAccount++;
    numElements++;
}

int MemberList::size() const {
    return numElements;
}

string MemberList::name(int account) {
    return memberList[account - 1].name;
}

string MemberList::to_string() const {
    stringstream ss;

    ss << memberList[numElements - 1].name << " (account #: "
       << memberList[numElements - 1].account << ") was added.\n";

    return ss.str();
}

void MemberList::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    auto * tempArr = new Member[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = memberList[i];

    // delete old array
    delete [] memberList;

    // reassign old array to new array
    memberList = tempArr;
}