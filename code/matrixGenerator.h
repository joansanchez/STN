#ifndef matrixGenerator_h
#define matrixGenerator_h
#include <iostream>
#include <map>
#include <set>
#include "member.h"
#include "film.h"


using namespace std;

class MatrixGen{
  protected:
    map<string,Member*> membersInfo;
    map<string, set<string>> adjacencyMatrix;
    void updateRatingsAfterRead();
  public:
    void generateMatrix(map<string, Film*> films);
    map<string,Member*> getMembersInfo();
    map<string, set<string>> getAdjacencyMatrix();
    void showRatings();



};
#endif
