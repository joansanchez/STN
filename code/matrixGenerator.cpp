#include "matrixGenerator.h"

void MatrixGen::generateMatrix(map<string, Film*> films){
  map<string, Film*>::iterator it;
  for(it = films.begin(); it != films.end(); ++it){
    float ratingTmp = it->second->getRating();
    vector<string> membersTmp = it->second->getMemebers();
    for (int i = 0; i < membersTmp.size(); ++i){
        //ratings structure
        if (membersInfo.find(membersTmp[i]) != membersInfo.end()){
          membersInfo[membersTmp[i]]->addRating(ratingTmp);
        }
        else{
          membersInfo.insert(make_pair(membersTmp[i], new Member(ratingTmp)));
        }
    }
    updateRatingsAfterRead();
    showRatings();
  }
}
map<string,Member*> MatrixGen::getMembersInfo(){
  return membersInfo;
}
map<string, set<string>> MatrixGen::getAdjacencyMatrix(){
  return adjacencyMatrix;
}

void MatrixGen::updateRatingsAfterRead(){
  map<string,Member*>::iterator itera;
  for(itera = membersInfo.begin(); itera != membersInfo.end(); ++itera){
    itera->second->calcRating();


  }
}

void MatrixGen::showRatings(){
  map<string,Member*>::iterator itera;
  for(itera = membersInfo.begin(); itera != membersInfo.end(); ++itera){
    cout << itera->first << " " << itera->second->getRating()<<endl;
  }
}
