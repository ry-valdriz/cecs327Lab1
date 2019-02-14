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
  // int sizeOfArray = 9;
  // int a1[sizeOfArray];
  // int a2[sizeOfArray];
  int arr1[3][3];
  int arr2[3][3];

  string inFileName1 = "";
  string inFileName2 = "";
  ofstream outStream;

  Scanner scanner1;
  Scanner scanner2;

  //string element = "";

  Utils::CheckArgs(2, argc, argv, "infilename1 (first matrix) infilename2 (second matrix)");
  inFileName1 = static_cast<string>(argv[1]);
  inFileName2 = static_cast<string>(argv[2]);

  scanner1.openFile(inFileName1);
  scanner2.openFile(inFileName2);


  // int i = 0;
  int row = 0;
  int column = 0;

  while(scanner1.hasNext()){
    arr1[row][column] = scanner1.nextInt();
    column = (column+1)%3;
    if (column ==0){
        row++;
    }
  }

  while(scanner2.hasNext()){
    arr2[row][column] = scanner2.nextInt();
    column = (column+1)%3;
    if (column ==0){
        row++;
    }
  }

  // while (scanner1.hasNext()) { //1d array
  //   a1[i] = stoi(scanner1.next());
  //   i++;
  // }

  //  i = 0; //copy a1 to 2d array arr1
  // while(i<sizeOfArray){
  // arr1[row][column] = a1[i];
  // column = (column+1)%3;
  // if (column ==0){
  //     row++;
  // }
  // i++;
  // }


  // i=0;
  // while(scanner2.hasNext()){//1d array
  //   a2[i] = stoi(scanner2.next());
  //   i++;
  // }

  // while(i<sizeOfArray){//copy a2 into 2d array
  // arr2[row][column] = a2[i];
  // column = (column+1)%3;
  // if (column ==0){
  //     row++;
  // }
  // i++;
  // }

  // cout << "Array 1: " ;
  // for(int x = 0; x < 9; x++){ //check if scanning documents correctly
  //   cout << arr1[x] << " ";
  // }
  //
  // cout<< "\nArray 2: ";
  // for(int x = 0; x < 9; x++){
  //   cout << arr2[x] << " ";
  // }

  for(int i =0; i<3 ; i++){ //output first 2d array
    for(int j =0; j<3 ; j++){
      cout<<arr1[i][j];
    }
    cout<<endl;
  }

  cout << ""<<endl;
  return 0;


}
