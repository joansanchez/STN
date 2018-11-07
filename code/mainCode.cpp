#include <iostream>
#include <map>
#include <set>
#include "film.h"
#include "member.h"
#include "extraction.h"
#include "matrixGenerator.h"
using namespace std;


map<string, Film*> films;
map<string,Member*> membersInfo;
map<string, set<string>> adjacencyMatrix;


int main(){
  //extracting the data
  Extraction* ext = new Extraction();
  films=ext->extract(films);
  MatrixGen* matGen = new MatrixGen();
  matGen->generateMatrix(films);


}
