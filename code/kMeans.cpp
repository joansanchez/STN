#include "kMeans.h"

void kMeans::calcKMeans(map<string,Member*> membersInfo, int k){
  calcFirstCenters(membersInfo, k);
  int ite = 0;
  while (!estable){
    cout << "Iteration: " << ite << endl;
    ++ite;
    findNearestCenter(membersInfo);
    paintCenter();
    recalcCenter();
  }
  printColorMatrix();
}

void kMeans::printColorMatrix(){
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

void kMeans::calcFirstCenters(map<string,Member*> membersInfo, int k){
  estable = false;
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
    stack<pair<int,int>> stackTmp;
    newCenterCalc[i] = stackTmp;
    colors[tmp] = colCell[i];
    centerKeys.push_back(tmp);
  }
}

void kMeans::findNearestCenter(map<string,Member*> membersInfo){
  map<string,Member*>::iterator it;
  for (it = membersInfo.begin(); it != membersInfo.end(); ++it){
    int currentCentre;
    float currentDistance = 100000.0;
    map <int, pair<int, int>>::iterator itCenters;
    for(itCenters = centers.begin(); itCenters != centers.end(); ++itCenters){
      float tmpDist = calcDist(itCenters->second, it->second->getPoints());
      if (tmpDist < currentDistance){
        currentCentre = itCenters->first;
        currentDistance = tmpDist;
      }
    }
    colors[it->first] = colCell[currentCentre];
    newCenterCalc[currentCentre].push(it->second->getPoints());
  }
}

float kMeans::calcDist(pair<int,int> pCenter, pair<int, int>pNode){
  float toReturn = pow((pCenter.first-pNode.first),2) + pow((pCenter.second-pNode.second),2);
  return sqrt(toReturn);
}

void kMeans::paintCenter(){
  for (int i = 0; i < centerKeys.size(); ++ i){
    colors[centerKeys[i]] = "black";
  }
}

void kMeans::recalcCenter(){
  map <int, stack<pair<int,int>>>::iterator it;
  estable = true;
  for (it = newCenterCalc.begin(); it != newCenterCalc.end(); ++it){
    stack<pair<int,int>> tmpStack = it->second;
    int x = 0;
    int y = 0;
    int size = tmpStack.size();
    while (!tmpStack.empty()){
      pair<int,int> pairTmp = tmpStack.top(); tmpStack.pop();
      x += pairTmp.first;
      y += pairTmp.second;
    }
    cout << "old center: " << centers[it->first].first << ", " <<centers[it->first].second << "\t";
    cout << "new center: " << x/size << ", " << y/size << "\t";
    float dist = calcDist(centers[it->first], make_pair(x/size,y/size));
    cout << "dist: " << dist << endl;
    if(dist< 1.0 and estable) estable = true;
    else estable = false;
    centers[it->first] = make_pair(x/size,y/size);
  }
}
