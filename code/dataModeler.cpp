#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
using namespace std;

vector<string> films;

void ratings(){
  ifstream file("../dataSet/small/title.basics.tsv"); // pass file name as argment
	string linebuffer;
  ofstream myfile;
  myfile.open ("../dataSet/small/title.ratings.tsv");
  while (file && getline(file, linebuffer)){
    if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string partial;
      getline(iss, partial, '\t');
      films.push_back(partial);
      random_device rd; // obtain a random number from hardware
      mt19937 eng(rd()); // seed the generator
      uniform_int_distribution<> distr(10, 500);
      int numberVotes = distr(eng);
      uniform_int_distribution<> distr2(10, 99);
      float newRating = float(distr2(eng)/10.0);
      myfile << partial << "\t" << newRating << "\t" << numberVotes << endl;
    }
  }
}

void names(){
  ifstream file("../dataSet/small/name.basics.tsv"); // pass file name as argment
	string linebuffer;
  ofstream myfile;
  myfile.open ("../dataSet/small/name.basics.modified.tsv");
  while (file && getline(file, linebuffer)){
    if (linebuffer.length() != 0){
      istringstream iss(linebuffer);
      string partial;
      getline(iss, partial, '\t');
      myfile << partial << "\t";
      random_device rd; // obtain a random number from hardware
      mt19937 eng(rd()); // seed the generator
      uniform_int_distribution<> distr(1, 9);
      int nfilms = distr(eng);
      uniform_int_distribution<> distr2(0, 199);
      for (int i = 0; i < nfilms; ++i){
        if (i != 0) myfile << ",";
        myfile << films[distr2(eng)];
      }
      myfile << endl;
    }
  }
}

int main(){
  ratings();
  names();
}
