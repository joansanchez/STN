#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
  ifstream file("test.txt"); // pass file name as argment
	string linebuffer;

	while (file && getline(file, linebuffer)){
	  if (linebuffer.length() != 0){
       //codigo aqui
    }
	}
}
