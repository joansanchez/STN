#ifndef member_h
#define member_h
#include <iostream>
#include <queue>
using namespace std;

class Member{
  protected:
    float rating;
    queue <float> queueRatings;
    int x;
    int y;
  public:
    Member(float ratingIn);
    void addRating(float newRating);
    void calcRating();
    float getRating();
    void setPoints(int xin, int yin);
    pair<int, int> getPoints();
};
#endif
