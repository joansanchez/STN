#include <iostream>
#include <vector>
using namespace std;


class Film{
  protected:
    float rating;
    vector<string> members;
  public:

    void updateRating(float newRating);

    void addMember(string newMember);

    vector<string> getMemebers();

    float getRating();

};
