/*

HELPER HEADER FILE 

Name: Jayathi Bandarupalli

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_FEATURES 16   // not including animal name and class label
#define NUM_SAMPLES 100      // total number of samples / rows in the given zoo dataset
#define NUM_CLASSES 7        // total number of class labels in zoo dataset
#define NUM_TEST_DATA 20     // total number of samples / rows in the test dataset - you need this for task 9
#define MAX_LENGTH_ANIMAL_NAME 50

/* Prototype for bubbleSort function */
void selectionSort(float distances[NUM_SAMPLES], int indices[NUM_SAMPLES], int increasing);
