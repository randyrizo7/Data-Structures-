

#ifndef PROJECT1_MEMBERLIST_H
#define PROJECT1_MEMBERLIST_H


#include <string>
using namespace std;

class MemberList {
public:
    explicit MemberList(int);

    ~MemberList();
    // add member
    void add(string);

    // size of member list
    int size() const;

    // varibale to hold names
    string name(int);

    // to string method
    string to_string() const;


private:
    struct Member {
        int account;                // index of memberList array
        string name;                // name of member
    };
    Member * memberList;            //  array

    int aAccount;                   // index of memberList array
    int capacity;                   // capacity of memberList array
    int numElements;                // Number of elements

    void resize();                  // resize array
};


#endif //PROJECT1_MEMBERLIST_H
