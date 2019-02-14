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


//void *matrix_mult(void *t) {
//
//}

int main (int argc, char *argv[]) {
    string inFileName1 = "";
    string inFileName2 = "";
    ofstream outStream;
    
    Scanner scanner1;
    Scanner scanner2;
    
    Utils::CheckArgs(2, argc, argv, "infilename (first matrix) outfilename (second matrix)");
    inFileName1 = static_cast<string>(argv[1]);
    inFileName2 = static_cast<string>(argv[2]);
    
    scanner1.openFile(inFileName1);
    scanner2.openFile(inFileName2);
    
    int first_input[3][3];
    int second_input[3][3];
    
    int row =0;
    int column =0;
    while (scanner1.hasNext()) {
        
        first_input[row][column] = stoi(scanner1.next());
        column = (column+1)%3;
        if (column ==0){
            row++;
        }
    }
    
    while (scanner2.hasNext()) {
        
        second_input[row][column] =  stoi(scanner1.next());
        column = (column+1)%3;
        if (column ==0){
            row++;
        }
    }
    
    for(int i =0; i<3 ; i++){
        for(int j =0; j<3 ; j++){
            cout<<first_input[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i =0; i<3 ; i++){
        for(int j =0; j<3 ; j++){
            cout<<second_input[i][j];
        }
        cout<<endl;
    }
    
}

