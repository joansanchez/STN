#include "kMeans.h"

void kMeans::calcKMeans(map<string,Member*> membersInfo, int k){
  calcFirstCenters(membersInfo, k);
  printColors();
}

void kMeans::printColorMatrix(){

}

void kMeans::calcFirstCenters(map<string,Member*> membersInfo, int k){
  map<string,Member*>::iterator it;
  for (it=membersInfo.begin(); it!= membersInfo.end(); ++it){
    mapKeys.push_back(it->first);
    colors.insert(make_pair(it->first, "violet"));
  }
  random_device rd; // obtain a random number from hardware
  mt19937 eng(rd()); // seed the generator
  uniform_int_distribution<> distr(0, mapKeys.size());
  for (int i = 0; i<k; ++i){
    string tmp = mapKeys[distr(eng)];
    centers[i] = membersInfo[tmp]->getPoints();
    colors[tmp] = colCell[i];
  }
}

void kMeans::printColors(){
  cout << "Writing on file NodeColors.txt" << endl;
  ofstream myfile;
  myfile.open ("outputs/NodeColors.txt");
  map <string, string>::iterator it;
  for (it = colors.begin(); it != colors.end(); ++it){
    myfile << it->first << " " << it->second << endl;
  }
  myfile.close();
  cout << "Writing on file NodeColors.txt completed" << endl;
}
