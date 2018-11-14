#include "influencerSearcher.h"

void influencerSearcher::updateRatingsInfluence(map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix){
  cout << "Computing validator influenecers"  << endl;
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
  cout << "Computing validator influenecers completed"  << endl;
  //printNewRatings();
}

map <string, float> influencerSearcher::getNewRatings(){
  return newRatings;
}

void influencerSearcher::pageRankAl(map<string,Member*> membersInfo, map<string, set<string>> adjacencyMatrix, float systemFame){
  int iterations;
  cout << "PAGERANK:" << endl;
  cout << "Define the number of iterations for the PageRank algorithm. Usually between 10 and 20 it's enough." << endl;
  cin >> iterations;
  float sValue;
  cout << "As we are using scaled PageRank, define a s-factor value between 0.1 and 0.9. Use point for the decimals."<< endl;
  cin >> sValue;
  map <string, float> fastInitialization;
  map <string, set<string>>::iterator it1;
  float size = 1.0/adjacencyMatrix.size();
  for(it1 = adjacencyMatrix.begin(); it1 != adjacencyMatrix.end(); ++it1){
    newRatingsPageRank[it1->first] = (membersInfo[it1->first]->getRating())/systemFame;
    fastInitialization[it1->first] = 0.0;
  }
  for (int i = 0; i < iterations; ++i){
    newRatingsPageRankTmp = fastInitialization;
    for(it1 = adjacencyMatrix.begin(); it1 != adjacencyMatrix.end(); ++it1){
      set<string> tmp = it1->second;
      set<string>::iterator it2;
      for (it2 = tmp.begin(); it2 != tmp.end(); ++it2){
        newRatingsPageRankTmp[*it2] += newRatingsPageRank[it1->first]/tmp.size();
      }
    }
    map <string, float>::iterator it3;
    for (it3 = newRatingsPageRankTmp.begin(); it3 != newRatingsPageRankTmp.end(); ++it3){
      newRatingsPageRankTmp[it3->first] = (1-sValue)/adjacencyMatrix.size() + newRatingsPageRankTmp[it3->first] * sValue;
    }
    newRatingsPageRank = newRatingsPageRankTmp;
  }
  cout << "PageRank performed successfully" << endl;
}

void influencerSearcher::printNewRatings(){
  map <string, float>::iterator tmpIt;
  for(tmpIt = newRatings.begin(); tmpIt != newRatings.end(); ++tmpIt){
    cout << tmpIt->first << " " <<tmpIt->second << endl;
  }
}
void influencerSearcher::printNewRatingsPageRank(){
  map <string, float>::iterator tmpIt;
  for(tmpIt = newRatingsPageRank.begin(); tmpIt != newRatingsPageRank.end(); ++tmpIt){
    cout << tmpIt->first << " " <<tmpIt->second << endl;
  }
}

void influencerSearcher::findInfluencersCommunity(map<string, string> colors, map<string,Member*> membersInfo)
{
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
  cout << "Writing on file NodeCenters.txt" << endl;
  cout << "Writing on file NodeCentersByAdjacncy.txt" << endl;
  cout << "Writing on file NodeCentersByPageRank.txt" << endl;
  ofstream myfile("outputs/NodeCenters.txt", ios::app);
  ofstream myfile2("outputs/NodeCentersByAdjacncy.txt", ios::app);
  ofstream myfile3("outputs/NodeCentersByPageRank.txt", ios::app);
  map <string, pair<string, float>>::iterator it1;
  for(it1 = topMembersCommunity.begin(); it1 != topMembersCommunity.end(); ++it1){
    pair <int, int> tmp = membersInfo[it1->second.first]->getPoints();
    myfile << "infl" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
    myfile2 << "infl" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
    myfile3 << "infl" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
  }
  cout << "Writing on file NodeCenters.txt completed" << endl;
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
  while (file && getline(file, linebuffer)){
    if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string partial;
      iss >> partial;
      if(partial[0] == 'i') {
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
    myfile << "Distance between node with more adjacencies and validator node in community " <<names[i] << ": " << calcDist(distances[i], distances[i+numbDist]) << endl;
  }
  cout << "Writing on file NodeCentersByAdjacncy.txt completed" << endl;
}


void influencerSearcher::findInfluencersCommunityPageRank(map<string, string> colors, map<string,Member*> membersInfo)
{
  map<string, string>::iterator it;
  for(it = colors.begin(); it != colors.end(); ++it){
    if (topPageRankMembers.find(it->second) != topPageRankMembers.end()){
      if(newRatingsPageRank[it->first] > topPageRankMembers[it->second].second){
        topPageRankMembers[it->second]=make_pair(it->first, newRatingsPageRank[it->first]);
      }
    }
    else{
      topPageRankMembers[it->second]=make_pair(it->first, newRatingsPageRank[it->first]);
    }
  }
  ofstream myfile("outputs/NodeCentersByPageRank.txt", ios::app);
  map <string, pair<string, float>>::iterator it1;
  for(it1 = topPageRankMembers.begin(); it1 != topPageRankMembers.end(); ++it1){
    pair <int, int> tmp = membersInfo[it1->second.first]->getPoints();
    myfile << "rank" <<it1->first << " " << tmp.first << " " << tmp.second << endl;

  }
  ifstream file("outputs/NodeCentersByPageRank.txt"); // pass file name as argment
  string linebuffer;
  vector<pair<int,int>> distances;
  vector<char> names;
  int numbDist = 0;
  while (file && getline(file, linebuffer)){
    if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string partial;
      iss >> partial;
      if(partial[0] == 'i') {
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
    myfile << "Distance between node with more pageRank and validator node in community " <<names[i] << ": " << calcDist(distances[i], distances[i+numbDist]) << endl;
  }
  cout << "Writing on file NodeCentersByPageRank.txt completed" << endl;
}
