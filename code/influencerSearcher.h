#ifndef influencerSearcher_h
#define influencerSearcher_h
#include <iostream>
#include <map>
#include <set>
#include "member.h"
using namespace std;

class influencerSearcher{
  protected:
    map <string, float> newRatings;
  public:
    void updateRatingsInfluence(map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix);
    map <string, float> getNewRatings();
    void printNewRatings();
};


#endif
