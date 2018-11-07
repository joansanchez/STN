#ifndef member_h
#define member_h
#include <iostream>
#include <queue>
using namespace std;

class Member{
  protected:
    float rating;
    queue <float> queueRatings;
  public:
    void addRating(float newRating);
    void calcRating();
    float getRating();
};
#endif
