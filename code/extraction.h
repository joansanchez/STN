#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "film.h"
using namespace std;

class Extraction{
  protected:

  public:
    map<string, Film*> extract(map<string, Film*> films);
    map<string, Film*> readTitles(map<string, Film*> films);
    map<string, Film*> readRatings(map<string, Film*> films);
    map<string, Film*> readNames(map<string, Film*> films);
    void mapPrinter(map<string, Film*> films);

};
