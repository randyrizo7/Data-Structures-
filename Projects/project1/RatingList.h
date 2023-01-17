
#ifndef PROJECT1_RATINGLIST_H
#define PROJECT1_RATINGLIST_H


#include <string>
using namespace std;

class RatingList {
public:
    explicit RatingList(int);


    ~RatingList();



    void add(const string&);



    void rate(int, int, int);


    void resizeRow();


    void resizeCol();


    int returnOneRating(int, int);


private:
    int capacity;                   // capacity of bookList array
    int row, col;                   // scope of array
    void resize();                  // resize array
    int ** ratingList;              // 2D array


};


#endif //PROJECT1_RATINGLIST_H
