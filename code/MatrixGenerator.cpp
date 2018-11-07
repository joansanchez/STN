#ifndef film_h
#define film_h

#include <iostream>
#include <map>
#include "extraction.h"

using namespace std;
#endif

map<string, Film*> films;

int main(){
  Extraction* ext = new Extraction();
  films=ext->extract(films);
}
