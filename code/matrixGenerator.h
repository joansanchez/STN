#ifndef matrixGenerator_h
#define matrixGenerator_h
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <fstream>
#include <sstream>
#include "member.h"
#include "film.h"


using namespace std;

class MatrixGen{
  protected:
    map<string,Member*> membersInfo;
    map<string, set<string>> adjacencyMatrix;
    map<string, int> whichConnectedComponents;
    map<int, set<string>> connectedComponents;
    void updateRatingsAfterRead();
  public:
    void generateMatrix(map<string, Film*> films);
    map<string,Member*> getMembersInfo();
    map<string, set<string>> getAdjacencyMatrix();
    void showRatings();
    void showAdjacencyMatrix();
    void printToFile();
    void calcCoordinates();
    void organizeComponents();



};
#endif
