#include <iostream>
#include "film.h"
#include <string>
using namespace std;


void Film::updateRating(float newRating){
  rating = newRating;
}

void Film::addMember(string newMember){
  members.push_back(newMember);
}

vector<string> Film::getMemebers(){
  return members;
}

float Film::getRating(){
  return rating;
}

void Film::test(){
  cout << "working" << endl;
}
