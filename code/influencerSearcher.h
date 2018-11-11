#ifndef influencerSearcher_h
#define influencerSearcher_h
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <cmath>
#include "member.h"
using namespace std;

class influencerSearcher{
  protected:
    map <string, float> newRatings;
    map <string, pair<string, float>> topMembersCommunity;
    map <string, pair<string, int>> topAdjacencyMembers;
  public:
    void updateRatingsInfluence(map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix);
    map <string, float> getNewRatings();
    void printNewRatings();
    void findInfluencersCommunity(map<string, string> colors, map<string,Member*> membersInfo);
    void findImportantNodeCommunity(map<string, string> colors, map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix);
    float calcDist(pair<int,int> pCenter, pair<int, int>pNode);
};


#endif
