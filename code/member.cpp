#include "member.h"

Member::Member(float ratingIn){
  addRating(ratingIn);
}
void Member::addRating(float newRating){
  queueRatings.push(newRating);
}
void Member::calcRating(){
  float tmp = 0.0f;
  int numberElements = 0;
  while (!queueRatings.empty()){
    float queueFront = queueRatings.front();
    tmp += queueFront;
    if (queueFront != 0.0f) ++numberElements;
    queueRatings.pop();
  }
  if (numberElements != 0)  rating = tmp/numberElements;
  else rating = 0;
}
float Member::getRating(){
  return rating;
}
