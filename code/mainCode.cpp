#include <iostream>
#include <map>
#include <set>
#include "film.h"
#include "extraction.h"
#include "matrixGenerator.h"
#include "influencerSearcher.h"
using namespace std;


map<string, Film*> films;

int main(){
  //extracting the data
  Extraction* ext = new Extraction();
  films=ext->extract(films);
  MatrixGen* matGen = new MatrixGen();
  matGen->generateMatrix(films);
  influencerSearcher* inSear = new influencerSearcher();
  inSear->updateRatingsInfluence(matGen->getMembersInfo(),matGen->getAdjacencyMatrix());


}
