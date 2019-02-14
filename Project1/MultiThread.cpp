#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"

#define NUM_THREADS 9


void *matrix_mult(void *t) {

}

int main (int argc, char *argv[]) {
  int arr1[9];
  int arr2[9];

  string inFileName1 = "";
  string inFileName2 = "";
  ofstream outStream;

  Scanner scanner1;
  Scanner scanner2;

  string element = "";

  Utils::CheckArgs(2, argc, argv, "infilename1 (first matrix) infilename2 (second matrix)");
  inFileName1 = static_cast<string>(argv[1]);
  inFileName2 = static_cast<string>(argv[2]);

  scanner1.openFile(inFileName1);
  scanner2.openFile(inFileName2);


  int i = 0;

  while (scanner1.hasNext()) {
    arr1[i] = stoi(scanner1.next());
    i++;
  }

  i=0;
  while(scanner2.hasNext()){
    arr2[i] = stoi(scanner2.next());
    i++;
  }

  cout << "Array 1: " ;
  for(int x = 0; x < 9; x++){ //check if scanning documents correctly
    cout << arr1[x] << " ";
  }

  cout<< "\nArray 2: ";
  for(int x = 0; x < 9; x++){
    cout << arr2[x] << " ";
  }

  cout << ""<<endl;
  return 0;


}
