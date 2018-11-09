#include "matrixGenerator.h"

void MatrixGen::generateMatrix(map<string, Film*> films){
  cout << "Generating adjacency matrix" << endl;
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
        //adjacencyMatrix structure
        if (membersTmp.size() == 1){
          set<string> setTmp;
          adjacencyMatrix.insert(make_pair(membersTmp[i], setTmp));
        }
        for(int j = 0; j < membersTmp.size(); ++j){
          if (i != j){
            if (adjacencyMatrix.find(membersTmp[i]) != adjacencyMatrix.end()){
              adjacencyMatrix[membersTmp[i]].insert(membersTmp[j]);
            }
            else {
              set<string> setTmp;
              setTmp.insert(membersTmp[j]);
              adjacencyMatrix.insert(make_pair(membersTmp[i], setTmp));
            }
          }
        }
    }
  }
  updateRatingsAfterRead();
  //showRatings();
  //showAdjacencyMatrix();
  printToFile();
  calcCoordinates();
  cout << "Generating adjacency matrix completed" << endl;
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

void MatrixGen::showAdjacencyMatrix(){
  map<string, set<string>>::iterator itera;
  for(itera = adjacencyMatrix.begin(); itera != adjacencyMatrix.end(); ++itera){
    cout << itera->first << "\t";
    set<string> tmpSet = itera->second;
    set<string>::iterator it;
    for (it = tmpSet.begin(); it != tmpSet.end(); ++it){
        cout << *it << " "; // Note the "*" here
    }
    cout << endl;
  }
}

void MatrixGen::printToFile(){
  cout << "Writing on file AdjacencyMatrix.txt" << endl;
  ofstream myfile;
  myfile.open ("outputs/AdjacencyMatrix.txt");
  map<string, set<string>>::iterator itera;
  for(itera = adjacencyMatrix.begin(); itera != adjacencyMatrix.end(); ++itera){
    myfile << itera->first << "\t";
    set<string> tmpSet = itera->second;
    set<string>::iterator it;
    for (it = tmpSet.begin(); it != tmpSet.end(); ++it){
        myfile << *it << " ";
    }
    myfile << endl;
  }
  myfile.close();
  cout << "Writing on file AdjacencyMatrix.txt completed" << endl;
}

void MatrixGen::calcCoordinates(){
  organizeComponents();
  map<string, int>::iterator itprint;
  for (itprint = whichConnectedComponents.begin(); itprint != whichConnectedComponents.end(); ++itprint){
    cout << itprint->first << " " << itprint->second << endl;
  }
}

void MatrixGen::organizeComponents(){
  int actualComponent = 0;
  stack<string> S;
  map<string, set<string>>::iterator iter;
  for(iter = adjacencyMatrix.begin(); iter != adjacencyMatrix.end(); ++iter){
    S.push(iter->first);
    while (not S.empty()){
      string top = S.top(); S.pop();
      if (whichConnectedComponents.find(top) == whichConnectedComponents.end()){
        whichConnectedComponents[top] = actualComponent;
        set<string>::iterator itSet;
        set<string> tmpSet = adjacencyMatrix[top];
        for (itSet = tmpSet.begin(); itSet != tmpSet.end(); ++itSet){
          S.push(*itSet);
        }
      }
    }
    ++actualComponent;
  }
}
