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
