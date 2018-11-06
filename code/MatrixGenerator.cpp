#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "film.h"
using namespace std;

map<string, Film*> films;

void readTitles(){
  cout << "Reading films IDs" << endl;
  ifstream file("../dataSet/small/title.basics.tsv"); // pass file name as argment
	string linebuffer;

	while (file && getline(file, linebuffer)){
	  if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string partial;
      getline(iss, partial, '\t'); //partial stores the id of the films to store
      films.insert(make_pair(partial, new Film()));
    }
	}
  cout << "Reading films IDs completed" << endl;
}

void readRatings(){
  cout << "Reading films ratings" << endl;
  ifstream file("../dataSet/small/title.ratings.tsv"); // pass file name as argment
	string linebuffer;

	while (file && getline(file, linebuffer)){
	  if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string titleID;
      float titleRating;
      getline(iss, titleID, '\t'); //partial stores the id of the films to store
      iss >> titleRating;
      films[titleID]->updateRating(titleRating);
    }
	}
  cout << "Reading films ratings completed" << endl;
}

void readNames(){
  cout << "Reading film members" << endl;
  ifstream file("../dataSet/small/name.basics.tsv"); // pass file name as argment
	string linebuffer;

	while (file && getline(file, linebuffer)){
	  if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string nameMember;
      getline(iss, nameMember, '\t'); //partial stores the id of the films to store
      string tmp;
      for (int i = 0; i <= 4; ++i) iss >> tmp; //we don't need this values
      string filmsMember;
      iss >> filmsMember;
      cout << filmsMember << endl;
      istringstream iss2(filmsMember); //el error esta por aqui
      string filmToInput;
      while(getline(iss2, filmToInput, ',')){
        films[filmToInput]->addMember(nameMember);
      }
    }
	}
  cout << "Reading film members completed" << endl;
}

void mapPrinter(){
  map<string, Film*>::iterator it ;
  for(it = films.begin(); it != films.end(); ++it){
    cout << it->first << " " << it->second->getRating()<< " ";
    vector<string> members = it->second->getMemebers();
    for(int i = 0; i < members.size(); ++i)cout << members[i] << " ";
    cout << endl;
  }
}

int main(){
  readTitles();
  readRatings();
  readNames();
  mapPrinter();
}
