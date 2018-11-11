#ifndef kMeans_h
#define kMeans_h
#include <iostream>
#include <map>
#include <stack>
#include <random>
#include <fstream>
#include <sstream>
#include <cmath>
#include "member.h"
using namespace std;

class kMeans{
  protected:
    bool estable;
    map <string, string> colors;
    vector<string> mapKeys;
    vector<string> colCell {"b", "g", "r", "c", "m", "y", "purple", "orange", "salmon", "maroon"};
    map <string, pair<int, int>> centers;
    map <string, stack<pair<int,int>>> newCenterCalc;
    vector<string> centerKeys;
    ofstream myfile2;
  public:
    void calcKMeans(map<string,Member*> membersInfo, int k);
    void printColorMatrix();
    void calcFirstCenters(map<string,Member*> membersInfo, int k);
    void findNearestCenter(map<string,Member*> membersInfo);
    void recalcCenter();
    void printCenters();
    float calcDist(pair<int,int> pCenter, pair<int, int>pNode);
    map <string, string> getColors();
};

#endif
