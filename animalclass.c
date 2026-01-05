#include "givenA1.h"
#include "helper.h"

/* Task 1 */
/*This function must read the information from a text file called 
a1Data.txt and store them in the array called dataZoo, where each element 
of the array is of type struct Animal. There are 100 lines in the given text file,
 where each line stores information of a single animal. For example, content of line 
 1 of a1Data.txt will be assigned to dataZoo [0] as the following:*/

int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]){
    
    //file pointer 
    FILE * fptr;
    //declare and intitialize i to 0
    int i =0;
    
    //open file in read mode 
    fptr = fopen(fName, "r");

    //check if file is null
    if(fptr == NULL){
        //printf("Error Acessing File\n");
        return -1;
    }

    //Using a while loop to store information from file 
    while(!feof(fptr)){

        //store file content using fscanf 
        fscanf(fptr,"%s %d %d %d %d %d %d %d %d %d %d %d %d  %d %d %d %d %d", dataZoo[i].animalName, &dataZoo[i].features[0], 
        &dataZoo[i].features[1], &dataZoo[i].features[2], &dataZoo[i].features[3], &dataZoo[i].features[4], &dataZoo[i].features[5],
         &dataZoo[i].features[6], &dataZoo[i].features[7], &dataZoo[i].features[8], &dataZoo[i].features[9], &dataZoo[i].features[10], 
         &dataZoo[i].features[11], &dataZoo[i].features[12], &dataZoo[i].features[13], &dataZoo[i].features[14],&dataZoo[i].features[15], &dataZoo[i].classLabel);

        i++; //increment i
    }

    //Storing info using for loop - Alternative 
    // for(int i=0; i< NUM_SAMPLES; i++){
    //     fscanf(fptr,"%s", dataZoo[i].animalName);
    //     //printf("animalName = %s\n", dataZoo[i].animalName);

    //     //printf("features = ");
    //     for(int j=0; j<NUM_FEATURES; j++){
    //         fscanf(fptr,"%d", &dataZoo[i].features[j]);
    //         //printf("%d ",  dataZoo[i].features[j]);
    //     }
    //     fscanf(fptr,"%d", &dataZoo[i].classLabel);
    //     //printf("\nclassLabel = %d\n\n",  dataZoo[i].classLabel);
    // }
   
    //close the file 
    fclose(fptr);

    return 1; //sucess in opening file
}

/* Task 2 */
void distanceFunctions (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES], float * euclideanDistance, int * hammingDistance, float * jaccardSimilarity){
    //set counts to 0 for number of zero and one matches in vectors 
    int oneCountMatches = 0; 
    int zeroCountMatches = 0;

    //initialize distances to 0 
    *euclideanDistance = 0;
    *hammingDistance = 0;
    *jaccardSimilarity = 0;
    

    //Euclidean Distance Calculation based on given vectors 
    for(int i = 0; i<NUM_FEATURES; i++){
        //using euclidean distance forumla 
        *euclideanDistance += pow(vector1 [i] - vector2[i], 2);
    }
    *euclideanDistance = sqrt(*euclideanDistance);

    //Hamming Distance Calculation based on given vectors 
    for(int i = 0; i<NUM_FEATURES; i++){
        //count number of times vector values are not equal
        if(vector1 [i] != vector2[i]){
            (*hammingDistance)++; //increment 
        }
    }

    //Jaccard Similarity Calculation based on given vectors
    for(int i = 0; i<NUM_FEATURES; i++){
        //if BOTH vector values are 1 
        if((vector1[i] == 1) && (vector2[i] == 1)){
            oneCountMatches++; //increment 
        }
    }

    //loop for if both vector values are equal to 0
    for(int i = 0; i<NUM_FEATURES; i++){
        if((vector1[i] == 0) && (vector2[i] == 0)){
            zeroCountMatches++; //increment
        }
    }
    //calculate similarity usign formula 
    *jaccardSimilarity = (float)oneCountMatches/(NUM_FEATURES - zeroCountMatches);
}


/* Task 3 */
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){
/*
struct Animal dataZoo [NUM_SAMPLES] - given dataset
int newSample [NUM_FEATURES] - features of new data sample ()
int k - total neighbors to find 
int whichDistanceFunction - index of desired distance function - this index can be 1,2 or 3 
1 represents Euclidean dist, 2 - hamming dist, 3-Jaccard’s similarity 
int kNearestNeighbors [NUM_SAMPLES]) - outputs array kNearestNeighbors 
that stores indices of the k nearest neighbors
*/


    //declare variables needed 
    float euclideanDist;
    float jaccardSim;
    int hammingDist; 

    float distances[NUM_SAMPLES];
    int indices[NUM_SAMPLES];
    int increasing;
    
    for(int i=0; i<NUM_SAMPLES; i++){
        indices[i] = i;

        //reset 
        euclideanDist = 0;
        hammingDist = 0;
        jaccardSim = 0;

        //call distance function
        distanceFunctions(newSample, dataZoo[i].features, &euclideanDist, &hammingDist, &jaccardSim);
        //printf("%f %d %f\n\n", euclideanDist, hammingDist, jaccardSim);

        // Store distance in temporary array (distance) based on what main passed
        if (whichDistanceFunction == 1){
            distances[i] = euclideanDist;  // Euclidean Distance
            increasing =1; //since we want 
        } 
        else if (whichDistanceFunction == 2){
            distances[i] = (float)hammingDist; 
            increasing = 1;
        } 
        else if (whichDistanceFunction == 3){
            distances[i] = jaccardSim;
            increasing = 0;
        } 
        //printf("Index: %d, Euclidean: %f, Hamming: %d, Jaccard: %f\n", i, euclideanDist, hammingDist, jaccardSim);
        // Debugging: print Jaccard similarity
        //printf("Jaccard similarity for sample %d: %f\n", i, jaccardSim);
         
    }

    selectionSort(distances, indices, increasing);
    
    // if(k> NUM_SAMPLES){
    //     k = NUM_SAMPLES;
    // }


    for (int i = 0; i < k; i++) {
        kNearestNeighbors[i] = indices[i];  // Store the top k indices
    }

}

//SOURCE USED FOR SORTING - ChatGPT
// Selection sort to sort distances and their corresponding indices
void selectionSort(float distances[NUM_SAMPLES], int indices[NUM_SAMPLES], int increasing) {
  
    for (int i = 0; i < NUM_SAMPLES - 1; i++) {
        int minMaxIdx = i;

        for (int j = i + 1; j < NUM_SAMPLES; j++) {
            if ((increasing && distances[j] < distances[minMaxIdx]) || 
            (!increasing && distances[j] > distances[minMaxIdx])|| 
    (distances[j] == distances[minMaxIdx] && indices[j] < indices[minMaxIdx])) { // Sort in ascending order (Euclidean and Hamming)
                minMaxIdx = j;
            }
        }
        // Swap distances
        float tempDist = distances[i];
        distances[i] = distances[minMaxIdx];
        distances[minMaxIdx] = tempDist;

        // Swap indices
        int tempIndex = indices[i];
        indices[i] = indices[minMaxIdx];
        indices[minMaxIdx] = tempIndex;
    }
}

/* Task 4 */
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k){
    //declare & initialize 

    //store indexes of k nearest neighbors 
    int nearestK[k]; 
    //array for class of neighbour animals 
    int classOfNeighbor[k]; 
    //int variable to store number of occurences of classes and make it equal to 0
    int numOfOccurences = 0;
    
    //varibles to store largest occurence, final predicted class label and temp variable
    int largestOccurrence = 0;
    int predictedClass = 0;
    int classOfTestData;
   

    //call function find nearest neighbors 
    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, nearestK);

    //for loop to get class and store it to classOfNeighbor array
    for (int i = 0; i < k; i++) {

        //use the index of nearest neighbours and store the class label in the 
        classOfNeighbor[i] = dataZoo[nearestK[i]].classLabel;

        //if the class label is 0, which means it is not populated, we break 
        if (classOfNeighbor[i] == 0) {
            break; 
        }
    }

    //for loop to determine how many times neigbours have identical class labels 
    for (int i = 0; i < k; i++) {

        //set number of occurences to equal to zero
        numOfOccurences = 0;
        classOfTestData = classOfNeighbor[i]; //classOfTestData is the class we're currently checking

        //go through each neighbor in a for loop
        for (int j = 0; j < k; j++) {
            //if neighbor class is = testclass
            if (classOfNeighbor[j] == classOfTestData) {
                //increment the occurences count 
                numOfOccurences += classOfNeighbor[j] == classOfTestData;
            }
        }

        //if the number of occurrences is equal to largest and class is less than predicted
        if(numOfOccurences == largestOccurrence && classOfTestData < predictedClass){
            //then classoftestdata is predictedclass
            predictedClass = classOfTestData;
    
        }
        //if the occurrence is greater than largest 
        else if(numOfOccurences > largestOccurrence){
            //the greater occurrence is now the numOfOccurences 
            largestOccurrence = numOfOccurences;
            predictedClass = classOfTestData; //therefore predicted class is now the class of test data 
        }

    }

    //return the predicted class label to main
    return predictedClass;
}

/* Task 5 */
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k){
   
    //declare and initialize 
    int correctPLabels;
    int predictClassOfTestData;
    float calculate =0; 

    //for loop to go through the test data 
    for(int i=0; i<NUM_TEST_DATA; i++){
        //printf("%d ", testData[i].classLabel);

        //call the predict class function and store value
        predictClassOfTestData = predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);

        //printf("Data: %s, Actual: %d, Predicted: %d\n", testData[i].animalName, testData[i].classLabel, predictClassOfTestData);

        //print the value of predicted classes
        printf("%d ", predictClassOfTestData);

        //check if the predicted class is equal to the actual class (of the test data)
        if(predictClassOfTestData == testData[i].classLabel){
            correctPLabels++; //increment number of correct predicted labels if predicted = actual
        }
    
    }

    //formula for accuracy is # of correct predictions / total number of predictions
    calculate = (float)correctPLabels/NUM_TEST_DATA ;

    printf("\n");
    //print the number of correct labels
    printf("Number of Correct Labels: %d\n", correctPLabels);


    //printf("%f\n", calculate);

    

    return calculate; //return the accuracy percentage in decimal float form
}
