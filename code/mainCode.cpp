#include <iostream>
#include <map>
#include <set>
#include "film.h"
#include "extraction.h"
#include "matrixGenerator.h"
#include "influencerSearcher.h"
#include "kMeans.h"
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
  inSear->pageRankAl(matGen->getMembersInfo(),matGen->getAdjacencyMatrix(), matGen->getRatingSystem());
  int k;
  cout << "For the community detection algorithm, introduce the number of communities you want to find between 2 and 10:" << endl;
  cin >> k;
  kMeans* kmeans = new kMeans();
  kmeans->calcKMeans(matGen->getMembersInfo(), k);
  inSear->findInfluencersCommunity(kmeans->getColors(), matGen->getMembersInfo());
  inSear->findImportantNodeCommunity(kmeans->getColors(), matGen->getMembersInfo(), matGen->getAdjacencyMatrix());
  inSear->findInfluencersCommunityPageRank(kmeans->getColors(), matGen->getMembersInfo());
  cout << "---------------" << endl;
  cout << "Process completed. You can pot the results using the plotAdjacencyMatrix.ipynb file inside the output folder." << endl;
}
