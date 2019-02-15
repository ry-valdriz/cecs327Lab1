#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"

#define NUM_THREADS 9

int first_input[3][3];
int second_input[3][3];
int result_matrix[9];

void *matrix_mult(void *t) {
    long r = (long)t;
    long column = r%3;
    
    if(r<3){
        int first = first_input[0][0]*second_input[0][column];
        int second = first_input[0][1]*second_input[1][column];
        int third = first_input[0][2]*second_input[2][column];
        result_matrix[r]= first+second+third;
    }
    else if(r<6){
        int first = first_input[1][0]*second_input[0][column];
        int second = first_input[1][1]*second_input[1][column];
        int third = first_input[1][2]*second_input[2][column];
        result_matrix[r]= first+second+third;
    }
    else{
        int first = first_input[2][0]*second_input[0][column];
        int second = first_input[2][1]*second_input[1][column];
        int third = first_input[2][2]*second_input[2][column];
        result_matrix[r]= first+second+third;
    }
    
    return 0;
}

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
    
    
    int row =0;
    int column =0;
    while (scanner1.hasNext()) {
        first_input[row][column] = scanner1.nextInt();
        column = (column+1)%3;
        if (column ==0){
            row++;
        }
    }
    
    //reset the value of row and column
    row =0;
    column = 0;
    while (scanner2.hasNext()) {
        second_input[row][column] =  scanner2.nextInt();
        column = (column+1)%3;
        if (column ==0){
            row++;
        }
    }
    
    pthread_t threads[NUM_THREADS];
    int rc;
    void *status;
    
    for(int i= 0; i < NUM_THREADS; i++){
        
        rc = pthread_create(&threads[i], NULL, matrix_mult, (void *)i);
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    for( int k = 0; k < NUM_THREADS; k++ ) {
        rc = pthread_join(threads[k], &status);
        if (rc) {
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
        cout << "Main: completed thread id :" << k ;
        cout << "  exiting with status :" << status << endl;
    }
    sleep(1);
    
    for(int i= 0; i<NUM_THREADS;i++){
        cout<<result_matrix[i]<<endl;
    }
    
    return 0;
}

