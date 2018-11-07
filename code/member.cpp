#include "member.h"

void Member::addRating(float newRating){
  queueRatings.push(newRating);
}
void Member::calcRating(){
  float tmp = 0;
  int numberElements = 0;
  while (!queueRatings.empty()){
    tmp += queueRatings.front();
    ++numberElements;
    queueRatings.pop();
  }
  rating = tmp;
}
float Member::getRating(){
  return rating;
}
