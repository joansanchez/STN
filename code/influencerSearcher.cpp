#include "influencerSearcher.h"

void influencerSearcher::updateRatingsInfluence(map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix){
  cout << "Computing influenecers"  << endl;
  map<string, set<string>>::iterator itera;
  for(itera = adjacencyMatrix.begin(); itera != adjacencyMatrix.end(); ++itera){
    float newRating = 0.0f;
    set<string>::iterator it;
    set<string> tmpSet = itera->second;
    for (it = tmpSet.begin(); it != tmpSet.end(); ++it){
        newRating += membersInfo[itera->first]->getRating() - membersInfo[*it]->getRating();
    }
    newRatings.insert(make_pair(itera->first, newRating));
  }
  cout << "Computing influenecers completed"  << endl;
  //printNewRatings();
}

map <string, float> influencerSearcher::getNewRatings(){
  return newRatings;
}

void influencerSearcher::printNewRatings(){
  map <string, float>::iterator tmpIt;
  for(tmpIt = newRatings.begin(); tmpIt != newRatings.end(); ++tmpIt){
    cout << tmpIt->first << " " <<tmpIt->second << endl;
  }
}

void influencerSearcher::findInfluencersCommunity(map<string, string> colors, map<string,Member*> membersInfo){
  map<string, string>::iterator it;
  for(it = colors.begin(); it != colors.end(); ++it){
    if (topMembersCommunity.find(it->second) != topMembersCommunity.end()){
      if(newRatings[it->first] > topMembersCommunity[it->second].second){
        topMembersCommunity[it->second]=make_pair(it->first, newRatings[it->first]);
      }
    }
    else{
      topMembersCommunity[it->second]=make_pair(it->first, newRatings[it->first]);
    }
  }
  ofstream myfile("outputs/NodeCenters.txt", ios::app);
  ofstream myfile2("outputs/NodeCentersByAdjacncy.txt", ios::app);
  map <string, pair<string, float>>::iterator it1;
  for(it1 = topMembersCommunity.begin(); it1 != topMembersCommunity.end(); ++it1){
    pair <int, int> tmp = membersInfo[it1->second.first]->getPoints();
    myfile << "infl" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
    myfile2 << "infl" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
  }

  ifstream file("outputs/NodeCenters.txt"); // pass file name as argment
	string linebuffer;
  vector<pair<int,int>> distances;
  vector<char> names;
  int numbDist = 0;
  while (file && getline(file, linebuffer)){
    if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string partial;
      iss >> partial;
      if(partial[0] == 'c') {
        ++numbDist;
        names.push_back(partial[4]);
      }
      int temp1;
      int temp2;
      iss >>temp1;
      iss >>temp2;
      distances.push_back(make_pair(temp1, temp2));
    }
  }
  for (int i = 0; i < numbDist; ++ i){
    myfile << "Distance between k-means center and most influential node in community " <<names[i] << ": " << calcDist(distances[i], distances[i+numbDist]) << endl;
    myfile2 << "Distance between k-means center and most influential node in community " <<names[i] << ": " << calcDist(distances[i], distances[i+numbDist]) << endl;
  }

  /*
  map <string, pair<string, float>>::iterator it2;
  for(it2 = topMembersCommunity.begin(); it2 != topMembersCommunity.end(); ++it2){
    cout << it2->first << " " <<it2->second.first << " " <<it2->second.second << endl;
  }
  */
}

float influencerSearcher::calcDist(pair<int,int> pCenter, pair<int, int>pNode){
  float toReturn = pow((pCenter.first-pNode.first),2) + pow((pCenter.second-pNode.second),2);
  return sqrt(toReturn);
}

void influencerSearcher::findImportantNodeCommunity(map<string, string> colors, map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix){
  map<string, string>::iterator it;
  for(it = colors.begin(); it != colors.end(); ++it){
    if (topAdjacencyMembers.find(it->second) != topAdjacencyMembers.end()){
      if(adjacencyMatrix[it->first].size() > topAdjacencyMembers[it->second].second){
        topAdjacencyMembers[it->second]=make_pair(it->first, adjacencyMatrix[it->first].size());
      }
    }
    else{
      topAdjacencyMembers[it->second]=make_pair(it->first, adjacencyMatrix[it->first].size());
    }
  }
  ofstream myfile("outputs/NodeCentersByAdjacncy.txt", ios::app);
  map <string, pair<string, int>>::iterator it1;
  for(it1 = topAdjacencyMembers.begin(); it1 != topAdjacencyMembers.end(); ++it1){
    pair <int, int> tmp = membersInfo[it1->second.first]->getPoints();
    myfile << "adja" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
  }

  ifstream file("outputs/NodeCentersByAdjacncy.txt"); // pass file name as argment
	string linebuffer;
  vector<pair<int,int>> distances;
  vector<char> names;
  int numbDist = 0;
  int linact = 0;
  bool linActActive = true;
  while (file && getline(file, linebuffer)){
    linActActive = true;
    if (linebuffer.length() != 0){
      ++linact;
      istringstream iss(linebuffer);
      string partial;
      iss >> partial;
      if(partial[0] == 'c') {
        ++numbDist;
        linActActive = false;
        names.push_back(partial[4]);
      }
      if (!linActActive or linact > 3*numbDist){
        int temp1;
        int temp2;
        iss >>temp1;
        iss >>temp2;
        distances.push_back(make_pair(temp1, temp2));
      }
    }
  }
  for (int i = 0; i < numbDist; ++ i){
    myfile << "Distance between k-means center and node with more adjacencies within the community " <<names[i] << ": " << calcDist(distances[i], distances[i+numbDist]) << endl;
  }

}
