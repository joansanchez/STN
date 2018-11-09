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
  //showAdjacencyMatrix();
  printToFile();
  calcCoordinates();
  //showRatings();
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
    pair<int, int> position = itera->second->getPoints();
    cout << itera->first << " " << itera->second->getRating() << " position: " << position.first << " " << position.second <<endl;
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

void MatrixGen::printCoordinates(){
  cout << "Writing on file NodeCoordinates.txt" << endl;
  ofstream myfile;
  myfile.open ("outputs/NodeCoordinates.txt");
  map<string,Member*>::iterator it;
  for(it = membersInfo.begin(); it != membersInfo.end(); ++it){
    myfile << it->first << " ";
    pair<int, int> pos = it->second->getPoints();
    myfile << pos.first << " " << pos.second << endl;
  }
  myfile.close();
  cout << "Writing on file NodeCoordinates.txt completed" << endl;
}

void MatrixGen::calcCoordinates(){
  organizeComponents();
  insertIntoComponents();
  assignCoordinates();
  printCoordinates();
  //printComponents();


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

void MatrixGen::insertIntoComponents(){
  map<string, int>::iterator it;
  for (it = whichConnectedComponents.begin(); it != whichConnectedComponents.end(); ++it){
    if (connectedComponents.find(it->second) != connectedComponents.end()){
      connectedComponents[it->second].insert(it->first);
    }
    else {
      set<string> stmp;
      stmp.insert(it->first);
      connectedComponents.insert(make_pair(it->second, stmp));
    }
  }
}

void MatrixGen::assignCoordinates(){
  map<int, set<string>>::iterator it;
  for (it = connectedComponents.begin(); it != connectedComponents.end(); ++it){
    set<string> members = it->second;
    bool first = true;
    int x;
    int y;
    set<string>::iterator itIn;
    for (itIn = members.begin(); itIn != members.end(); ++itIn){
      if (first){
        first = false;
        random_device rd; // obtain a random number from hardware
        mt19937 eng(rd()); // seed the generator
        uniform_int_distribution<> distr(15, 85);
        x = distr(eng);
        y = distr(eng);
        membersInfo[*itIn]->setPoints(x, y);
      }
      else{
        random_device rd; // obtain a random number from hardware
        mt19937 eng(rd()); // seed the generator
        uniform_int_distribution<> distr(x-15, x+15);
        int xtmp = distr(eng);
        uniform_int_distribution<> distr2(y-15, y+15);
        int ytmp = distr2(eng);
        membersInfo[*itIn]->setPoints(xtmp, ytmp);
      }
    }
  }
}

void MatrixGen::printComponents(){
  map<string, int>::iterator itprint;
  for (itprint = whichConnectedComponents.begin(); itprint != whichConnectedComponents.end(); ++itprint){
    cout << itprint->first << " " << itprint->second << endl;
  }
  cout << "-----" << endl;

  map<int, set<string>>::iterator itprint2;
  for (itprint2 = connectedComponents.begin(); itprint2 != connectedComponents.end(); ++itprint2){
    cout << itprint2->first << " ";
    set<string>::iterator itera3;
    for(itera3 = itprint2->second.begin(); itera3 != itprint2->second.end(); ++itera3){
      cout << *itera3 << " ";
    }
    cout << endl;
  }
}
