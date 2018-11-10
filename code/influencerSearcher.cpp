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
  map <string, pair<string, float>>::iterator it1;
  for(it1 = topMembersCommunity.begin(); it1 != topMembersCommunity.end(); ++it1){
    pair <int, int> tmp = membersInfo[it1->second.first]->getPoints();
    myfile << "infl" <<it1->first << " " << tmp.first << " " << tmp.second << endl;
  }

  map <string, pair<string, float>>::iterator it2;
  for(it2 = topMembersCommunity.begin(); it2 != topMembersCommunity.end(); ++it2){
    cout << it2->first << " " <<it2->second.first << " " <<it2->second.second << endl;
  }
}
