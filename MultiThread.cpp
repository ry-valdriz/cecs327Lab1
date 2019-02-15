//===============================================================================================
//HW 1:     Matrix Multiplication w/ Multithreading
//Author:   Florence Yao
//Course:   CECS-327
//Date:     2-14-19
//Info:     This program performs a (3x3) matrix multiplication with multiple threads. Each
//          process is responsible for multiplying its respective row and column, given by
//          a self-defined struct "thread_data".
//===============================================================================================

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"
#define NUM_THREADS 9
#define NUM_ROWS 3
#define NUM_COLS 3
using namespace std;

//struct contains information for each thread
//each thread has a row, col and unique id
struct thread_data{
    int thread_num; //identifier
    int row;
    int col;
};

//global
int matrix_one[NUM_ROWS][NUM_COLS];
int matrix_two[NUM_ROWS][NUM_COLS];
int matrix_result[NUM_ROWS][NUM_COLS];

//function signatures
void* my_thread(void *arg);
void init_threads(struct thread_data *td);
void print(int m[NUM_ROWS][NUM_COLS]);
void file_in(int argc, char *argv[]);

int main (int argc, char *argv[]) {
    file_in(argc, argv); //get input from file
    pthread_t threads[NUM_THREADS]; //declare array containing pthread objects for thread creation
    struct thread_data td[NUM_THREADS]; //each thread will be created with my thread data struct
    init_threads(td);
    
    //create threads
    for(int i=0; i<NUM_THREADS; i++){
        if(pthread_create(&(threads[i]), NULL, &my_thread, (void *)&td[i]) != 0){
            cout<<"Error Creating Thread "<<i<<endl;
        }
    }
    
    //join threads
    for(int i=0; i<NUM_THREADS;i++){
        if(pthread_join(threads[i], NULL) != 0){
            cout<<"Error Joining thread "<<i<<endl;
        }
    }
    
    print(matrix_result);
    return 0;
}
//===============================================================================================
//function:    file_in()
//input(s):    argc, argv (command line args)
//output(s):   none
//description: this is your function that i copy/pasted.
//             each string is converted to an integer and stored into an array, then elements from
//             the array are put into matrix 1 and 2 which are global variables.
//===============================================================================================
void file_in(int argc, char *argv[]){
    string inFileName1 = "";
    string inFileName2 = "";
    ofstream outStream;
    
    Scanner scanner1;
    Scanner scanner2;
    
    string element = "";
    
    Utils::CheckArgs(2, argc, argv, "infilename (first matrix) outfilename (second matrix)");
    inFileName1 = static_cast<string>(argv[1]);
    inFileName2 = static_cast<string>(argv[2]);
    
    scanner1.openFile(inFileName1);
    scanner2.openFile(inFileName2);
    
    int arr1[NUM_ROWS*NUM_COLS]; //numbers from file input goes in here
    int arr2[NUM_ROWS*NUM_COLS];
    
    int i = 0;
    while (scanner1.hasNext()) {
        element = scanner1.next();
        //cout << element << endl;
        arr1[i] = atoi(element.c_str());
        i++;
    }
    
    int j = 0;
    while (scanner2.hasNext()) {
        element = scanner2.next();
        //cout << element << endl;
        arr2[j] = atoi(element.c_str());
        j++;
    }
    
    //initialize matrix
    int k = 0;
    for(int r=0; r<NUM_ROWS; r++){
        for(int c=0; c<NUM_COLS; c++){
            matrix_one[r][c] = arr1[k];
            matrix_two[r][c] = arr2[k];
            k++;
        }
    }
}

//===============================================================================================
//function:    my_thread()
//input(s):    void pointer
//output(s):   none
//description: each thread computes a row of matrix 1 and a column of matrix 2 in respect to
//             its element number in the result matrix. once the void pointer is casted into
//             the thread_data struct, each thread will know its own row and col. a thread
//             with r=0 and c=1 will input its result in r=0 and c=1 in the result matrix.
//===============================================================================================
void* my_thread(void *arg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) arg; //cast arg into my struct
    int r = my_data->row;
    int c = my_data->col;
    int id = my_data->thread_num;

    int result = 0;
    for(int i=0; i<NUM_ROWS; i++){
        result += matrix_one[r][i] * matrix_two[i][c];
    }
    matrix_result[r][c] = result;
    
    cout << "Thread " << id << " is done. " << endl;

    pthread_exit(NULL);
}

//===============================================================================================
//function:    init_threads()
//input(s):    pointer to thread data struct
//output(s):   none
//description: initializes each thread with row, col and ID stored in thread_data struct
//===============================================================================================
void init_threads(struct thread_data *td){
    int k = 0;
    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            td[k].thread_num = k;
            td[k].row = i;
            td[k].col = j;
            k++;
        }
    }
}

//===============================================================================================
//function:    print()
//input(s):    2D matrix
//output(s):   integers
//description: prints a 2D array
//===============================================================================================
void print(int m[NUM_ROWS][NUM_COLS]){
    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            cout << m[i][j] << " ";
        }
        cout << endl ;
    }
}
